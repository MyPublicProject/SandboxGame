// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SiAiHandObject.generated.h"

UCLASS()
class SANDBOXGAME_API ASiAiHandObject : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASiAiHandObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//根据物品ID返回物品的工厂方法 TSubclassOf ?
	static TSubclassOf<AActor> SpawnHandObject(int ObjectID);

	// 是否允许检测
	void ChangeOverlayDetect(bool IsOpen);

public:

	// 物品ID
	int ObjectIndex;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	// 根组件
	class USceneComponent *RootScene;

	// 静态模型
	UPROPERTY(EditAnywhere, Category = "SiAi")
		class UStaticMeshComponent *BaseMesh;

	// 盒子碰撞体
	UPROPERTY(EditAnywhere, Category = "SiAi")
		class UBoxComponent *AffectCollision;

};
