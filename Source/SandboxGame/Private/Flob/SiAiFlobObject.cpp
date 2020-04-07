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
	// ������ײ����
	BoxCollision->SetCollisionProfileName(FName("FlobProfile"));
	// ��������ģ��
	BoxCollision->SetSimulatePhysics(true);
	// ������ת
	BoxCollision->SetConstraintMode(EDOFMode::Default);
	BoxCollision->GetBodyInstance()->bLockXRotation = true;
	BoxCollision->GetBodyInstance()->bLockYRotation = true;
	BoxCollision->GetBodyInstance()->bLockZRotation = true;
	// ���ô�С
	BoxCollision->SetBoxExtent(FVector(15.f));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetCollisionResponseToChannels(ECR_Ignore);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//���ñ任
	BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.3f));

	UMaterialInterface* StaticObjectIconMat = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/FlobIconMatInst.FlobIconMatInst'"));
	// ��̬��������
	ObjectIconMatDynamic = UMaterialInstanceDynamic::Create(StaticObjectIconMat, nullptr);

}

// Called when the game starts or when spawned
void ASiAiFlobObject::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		// ע�����¼�
		FTimerDelegate DelectPlayerDele;
		DelectPlayerDele.BindUObject(this, &ASiAiFlobObject::DetectPlayer);
		GetWorld()->GetTimerManager().SetTimer(DetectTimer, DelectPlayerDele, 1.f, true, 3.f);
		
		// ע�������¼�
		FTimerDelegate DestroyDele;
		DestroyDele.BindUObject(this, &ASiAiFlobObject::DestroyEvent);
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, DestroyDele, 30.f, false);

		// ��ʼ���ָ��Ϊ��
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

	// ��������
	TArray<FOverlapResult> Overlaps;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.bTraceAsyncScene = true;

	// ��̬��⣬ ��Χ 200 
	if (GetWorld()->OverlapMultiByObjectType(Overlaps,GetActorLocation(), FQuat::Identity, ObjectParams,FCollisionShape::MakeSphere(200.f),Params))
	{
		for (TArray<FOverlapResult>::TIterator It(Overlaps); It; ++It) {
			//�����⵽�����
			if (Cast<ASiAiPlayerCharacter>(It->GetActor())) {
				//��ֵ
				SPCharacter = Cast<ASiAiPlayerCharacter>(It->GetActor());
				if (true)
				{
					//ֹͣ���
					GetWorld()->GetTimerManager().PauseTimer(DetectTimer);
					//ֹͣ���ٶ�ʱ��
					GetWorld()->GetTimerManager().PauseTimer(DestroyTimer);
					//�ر�����ģ��
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
	//ע����ʱ��
	GetWorld()->GetTimerManager().ClearTimer(DetectTimer);
	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
	//�����Լ�
	GetWorld()->DestroyActor(this);
}

// Called every frame
void ASiAiFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// һֱ��ת
	BaseMesh->AddLocalRotation(FRotator(DeltaTime * 60.f, 0.f, 0.f));

	// ������
	if (SPCharacter)
	{
		// �������
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f), DeltaTime, 5.f));
		// ����С��ָ����Χ
		if (FVector::Distance(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f,40.f)) < 10.f)
		{
			// �жϱ����Ƿ��пռ�
			if (true)
			{
				// ��Ӷ�Ӧ��Ʒ������
				// �����Լ�
				DestroyEvent();
			}
			else
			{
				// �����ұ�����Ϊ��
				SPCharacter = nullptr;
				// ���Ѽ��
				GetWorld()->GetTimerManager().UnPauseTimer(DetectTimer);
				// ���������߳�
				GetWorld()->GetTimerManager().UnPauseTimer(DetectTimer);
				// ��������ģ��
				BoxCollision->SetSimulatePhysics(true);
			}
		}
	}

}

void ASiAiFlobObject::CreateFlobObject(int ObjectID)
{
	// ָ�� ID
	ObjectIndex = ObjectID;

	// ��Ⱦ��ͼ
	RenderTexture();

	// ������������
	FRandomStream Stream;
	Stream.GenerateNewSeed();
	int DirYaw = Stream.RandRange(-180, 180);
	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);

	// �����
	BoxCollision->AddForce((FVector(0.f, 0.f, 4.f) + ForceRot.Vector()) * 100000.f);
}

void ASiAiFlobObject::ThrowFlobObject(int ObjectID, float DirYaw)
{

}

