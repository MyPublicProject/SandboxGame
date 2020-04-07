// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "SiAiFlobObject.generated.h"

UCLASS()
class SANDBOXGAME_API ASiAiFlobObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASiAiFlobObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 生成物品初始化
	void CreateFlobObject(int ObjectID);

	// 丢弃物品初始化，丢弃的物品ID和丢弃方向
	void ThrowFlobObject(int ObjectID, float DirYaw);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// 渲染贴图
	void RenderTexture();

	// 动态检测事件
	void DetectPlayer();

	// 销毁事件
	void DestroyEvent();

private:

	class UBoxComponent* BoxCollision;

	class UStaticMeshComponent* BaseMesh;

	//物品ID
	int ObjectIndex;

	class UTexture* ObjectIconTex;

	class UMaterialInstanceDynamic* ObjectIconMatDynamic;

	// 玩家指针
	class ASiAiPlayerCharacter *SPCharacter;

	// 动态检测 Timer
	FTimerHandle DetectTimer;

	// 销毁自个 Timer
	FTimerHandle DestroyTimer;
};
