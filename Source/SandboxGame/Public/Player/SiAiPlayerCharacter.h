// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AiSiTypes.h"
#include "SiAiPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UCharacterMovementComponent;
class UChildActorComponent;

UCLASS()
class SANDBOXGAME_API ASiAiPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASiAiPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 修改视角
	void ChangeView(EGameViewMode::Type NewGameView);

	// 修改当前的手持物品
	void ChangeHandObject(int32 Index);

public:

	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		USpringArmComponent *CameraBoom;
	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		UCameraComponent *ThirdCamera;
	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		UCameraComponent *FirstCamera;
	
	// 当前的视角模型
	EGameViewMode::Type GameView;

	// 上半身动画状态
	EUpperBody::Type UpperType;

	// 是否允许切换视角
	bool IsAllowSwitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookUpAtRate(float Value);

	void Turn(float Value);

	void TurnAtRate(float Value);

	void OnStartJump();

	void OnStopJump();

	void OnStartRun();

	void OnStopRun();

private:

	// 第一人称模型
	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		USkeletalMeshComponent *MeshFirst;

	// 手上物品
	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		UChildActorComponent *HandObject;

	// 旋转速率
	float BaseLookUpRate;
	float BaseTurnRate;
	
};
