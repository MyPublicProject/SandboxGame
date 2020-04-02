// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SiAiResourceObject.generated.h"

UCLASS()
class SANDBOXGAME_API ASiAiResourceObject : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASiAiResourceObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// 资源ID
	int ResourceIndex;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	// 根组件
	USceneComponent *RootScene;

	// 静态模型
	UStaticMeshComponent *BaseMesh;

	// 保存资源地址数组
	TArray<FString> ResourcePath;
	
};
