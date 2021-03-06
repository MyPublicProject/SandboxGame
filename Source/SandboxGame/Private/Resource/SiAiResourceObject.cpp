// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiResourceObject.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SlAiDataHandle.h"
#include "Flob/SiAiFlobObject.h"


// Sets default values
ASiAiResourceObject::ASiAiResourceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 实例化根组件
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// 实例化模型组件
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));

	// 开启交互检测
	BaseMesh->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void ASiAiResourceObject::BeginPlay()
{
	Super::BeginPlay();

	if (SlAiDataHandle::Get()->bIsGameData)
	{
		TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
		HP = BaseHP = ResourceAttr->HP;
	}
}

void ASiAiResourceObject::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	// 遍历生成掉落物
	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; It++)
	{
		// 随机生成的数量
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		// 生成数量
		int Num = Stream.FRandRange((*It)[1], (*It)[2]);

		if (GetWorld())
		{
			for (int i = 0; i < Num; i++)
			{
				// 生成掉落物
				ASiAiFlobObject *FlobObject = GetWorld()->SpawnActor<ASiAiFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 20.f), FRotator::ZeroRotator);
				FlobObject->CreateFlobObject((*It)[0]);
			}
		}
	}
}

// Called every frame
void ASiAiResourceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FText ASiAiResourceObject::GetInfoText() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ResourceAttr->EN;
		break;
	case ECultureTeam::ZH:
		return ResourceAttr->ZH;
		break;
	}
	return ResourceAttr->ZH;
}

EResourceType::Type ASiAiResourceObject::GetResourceType()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	return ResourceAttr->ResourceType;
}

float ASiAiResourceObject::GetHPRange()
{
	return FMath::Clamp<float>((float)HP / (float)BaseHP, 0.f, 1.f);
}

ASiAiResourceObject * ASiAiResourceObject::TakeObjectDamage(int Damage)
{
	HP = FMath::Clamp<int>(HP - Damage, 0, BaseHP);

	if (HP <= 0)
	{
		// 取消检测
		BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		// 创建掉落物
		CreateFlobObject();
		// 销毁
		if (GetWorld()) GetWorld()->DestroyActor(this);
	}
	return this;
}

