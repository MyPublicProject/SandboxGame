// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiFlobObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "SlAiDataHandle.h"
#include "AiSiTypes.h"
#include "Engine/Texture.h"
#include "Components/MeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UnrealMathUtility.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "SiAiPlayerCharacter.h"


// Sets default values
ASiAiFlobObject::ASiAiFlobObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = (USceneComponent*)BoxCollision;
	// 设置碰撞属性
	BoxCollision->SetCollisionProfileName(FName("FlobProfile"));
	// 启动物理模拟
	BoxCollision->SetSimulatePhysics(true);
	// 锁定旋转
	BoxCollision->SetConstraintMode(EDOFMode::Default);
	BoxCollision->GetBodyInstance()->bLockXRotation = true;
	BoxCollision->GetBodyInstance()->bLockYRotation = true;
	BoxCollision->GetBodyInstance()->bLockZRotation = true;
	// 设置大小
	BoxCollision->SetBoxExtent(FVector(15.f));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetCollisionResponseToChannels(ECR_Ignore);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//设置变换
	BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.3f));

	UMaterialInterface* StaticObjectIconMat = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/FlobIconMatInst.FlobIconMatInst'"));
	// 动态创建材质
	ObjectIconMatDynamic = UMaterialInstanceDynamic::Create(StaticObjectIconMat, nullptr);

}

// Called when the game starts or when spawned
void ASiAiFlobObject::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		// 注册检查事件
		FTimerDelegate DelectPlayerDele;
		DelectPlayerDele.BindUObject(this, &ASiAiFlobObject::DetectPlayer);
		GetWorld()->GetTimerManager().SetTimer(DetectTimer, DelectPlayerDele, 1.f, true, 3.f);
		
		// 注册销毁事件
		FTimerDelegate DestroyDele;
		DestroyDele.BindUObject(this, &ASiAiFlobObject::DestroyEvent);
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, DestroyDele, 30.f, false);

		// 初始玩家指针为空
		SPCharacter = nullptr;

	}
	
}

void ASiAiFlobObject::RenderTexture()
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex = LoadObject<UTexture>(NULL, *ObjectAttr->TexPath);
	ObjectIconMatDynamic->SetTextureParameterValue(FName("ObjectTex"), ObjectIconTex);
	BaseMesh->SetMaterial(0, ObjectIconMatDynamic);
}

void ASiAiFlobObject::DetectPlayer()
{
	if (!GetWorld()) return;

	// 保存检测结果
	TArray<FOverlapResult> Overlaps;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.bTraceAsyncScene = true;

	// 动态检测， 范围 200 
	if (GetWorld()->OverlapMultiByObjectType(Overlaps,GetActorLocation(), FQuat::Identity, ObjectParams,FCollisionShape::MakeSphere(200.f),Params))
	{
		for (TArray<FOverlapResult>::TIterator It(Overlaps); It; ++It) {
			//如果检测到了玩家
			if (Cast<ASiAiPlayerCharacter>(It->GetActor())) {
				//赋值
				SPCharacter = Cast<ASiAiPlayerCharacter>(It->GetActor());
				if (true)
				{
					//停止检测
					GetWorld()->GetTimerManager().PauseTimer(DetectTimer);
					//停止销毁定时器
					GetWorld()->GetTimerManager().PauseTimer(DestroyTimer);
					//关闭物理模拟
					BoxCollision->SetSimulatePhysics(false);
				}
				return;
			}
		}
	}
}

void ASiAiFlobObject::DestroyEvent()
{
	if (!GetWorld()) return;
	//注销定时器
	GetWorld()->GetTimerManager().ClearTimer(DetectTimer);
	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
	//销毁自己
	GetWorld()->DestroyActor(this);
}

// Called every frame
void ASiAiFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 一直旋转
	BaseMesh->AddLocalRotation(FRotator(DeltaTime * 60.f, 0.f, 0.f));

	// 检测玩家
	if (SPCharacter)
	{
		// 靠近玩家
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f), DeltaTime, 5.f));
		// 距离小于指定范围
		if (FVector::Distance(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f,40.f)) < 10.f)
		{
			// 判断背包是否有空间
			if (true)
			{
				// 添加对应物品到背包
				// 销毁自己
				DestroyEvent();
			}
			else
			{
				// 如果玩家背包不为空
				SPCharacter = nullptr;
				// 唤醒检测
				GetWorld()->GetTimerManager().UnPauseTimer(DetectTimer);
				// 唤醒销毁线程
				GetWorld()->GetTimerManager().UnPauseTimer(DetectTimer);
				// 开启物理模拟
				BoxCollision->SetSimulatePhysics(true);
			}
		}
	}

}

void ASiAiFlobObject::CreateFlobObject(int ObjectID)
{
	// 指定 ID
	ObjectIndex = ObjectID;

	// 渲染贴图
	RenderTexture();

	// 做随机方向的力
	FRandomStream Stream;
	Stream.GenerateNewSeed();
	int DirYaw = Stream.RandRange(-180, 180);
	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);

	// 添加力
	BoxCollision->AddForce((FVector(0.f, 0.f, 4.f) + ForceRot.Vector()) * 100000.f);
}

void ASiAiFlobObject::ThrowFlobObject(int ObjectID, float DirYaw)
{

}

