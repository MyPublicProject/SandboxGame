// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPickupObject.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASiAiPickupObject::ASiAiPickupObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 实例化根节点
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("PickupProfile"));

}

// Called when the game starts or when spawned
void ASiAiPickupObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASiAiPickupObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText ASiAiPickupObject::GetInfoText() const
{
	return FText::FromString("66");
}

