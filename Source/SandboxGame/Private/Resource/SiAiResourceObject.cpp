// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiResourceObject.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASiAiResourceObject::ASiAiResourceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ʵ���������
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// ʵ����ģ�����
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));

	// �����������
	BaseMesh->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void ASiAiResourceObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASiAiResourceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
