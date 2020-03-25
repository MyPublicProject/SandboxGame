// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SiAiPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API USiAiPlayerAnim : public UAnimInstance
{ 
	GENERATED_BODY()
	
public:

	USiAiPlayerAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	// 获取角色指针
	void InitSPCharacter();

	// 更新属性
	virtual void UpdateParameter();

protected:

	//角色指针
	class ASiAiPlayerCharacter* SPCharacter;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		FRotator SpineRotator;
};
