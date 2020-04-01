// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiHandObject.h"
#include "Engine/StaticMesh.h"
#include "ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

//�ֳ���Ʒ��
#include "SiAiHandNone.h"
#include "SiAiHandWood.h"
#include "SiAiHandStone.h"
#include "SiAiHandApple.h"
#include "SiAiHandMeat.h"
#include "SiAiHandAxe.h"
#include "SiAiHandHammer.h"
#include "SiAiHandSword.h"

#include "SiAiHelper.h"


// Sets default values
ASiAiHandObject::ASiAiHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ʵ���������
	RootScene = CreateDefaultSubobject<USceneComponent>("RootScene");
	RootComponent = RootScene;

	// ������̬ģ�����
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	// ʵ����ײ���
	AffectCollision = CreateDefaultSubobject<UBoxComponent>("AffectCollision");
	AffectCollision->SetupAttachment(RootComponent);
	AffectCollision->SetCollisionProfileName(FName("ToolProfile"));

	// ��ʼʱ�ر�Overlay���
	AffectCollision->bGenerateOverlapEvents = true;

	// �󶨼�ⷽ������ײ��
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);

}

// Called when the game starts or when spawned
void ASiAiHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASiAiHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SiAiHelper::Debug("OnOverlayBegin", 30.f);
}

void ASiAiHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SiAiHelper::Debug("OnOverlayEnd", 30.f);
}

// Called every frame
void ASiAiHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSubclassOf<AActor> ASiAiHandObject::SpawnHandObject(int32 ObjectID)
{
	switch (ObjectID)
	{
	case 0:
		return ASiAiHandNone::StaticClass();
	case 1:
		return ASiAiHandWood::StaticClass();
	case 2:
		return ASiAiHandStone::StaticClass();
	case 3:
		return ASiAiHandApple::StaticClass();
	case 4:
		return ASiAiHandMeat::StaticClass();
	case 5:
		return ASiAiHandAxe::StaticClass();
	case 6:
		return ASiAiHandHammer::StaticClass();
	case 7:
		return ASiAiHandSword::StaticClass();
	}

	return ASiAiHandNone::StaticClass();
}

