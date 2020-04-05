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

}

void ASiAiFlobObject::DestroyEvent()
{

}

// Called every frame
void ASiAiFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

