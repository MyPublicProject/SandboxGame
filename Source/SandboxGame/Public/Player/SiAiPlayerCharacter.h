// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SiAiPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UCharacterMovementComponent;

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

public:

	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		USpringArmComponent *CameraBoom;
	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		UCameraComponent *ThirdCamera;
	UPROPERTY(VisibleDefaultsOnly, Category = "SiAi")
		UCameraComponent *FirstCamera;

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

	// 旋转速率
	float BaseLookUpRate;
	float BaseTurnRate;

	
};
