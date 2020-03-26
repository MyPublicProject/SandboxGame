// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AiSiTypes.h"
#include "SiAiPlayerAnim.generated.h"

class UAnimMontage;
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

	// 更新动作
	virtual void UpdateMontage();

	// 是否允许切换视角
	void AllowViewChange(bool IsAllow);

protected:

	//角色指针
	class ASiAiPlayerCharacter* SPCharacter;

	//上半身的Montage
	UAnimMontage* PlayerHitMontage;
	UAnimMontage* PlayerFightMontage;
	UAnimMontage* PlayerPunchMontage;
	UAnimMontage* PlayerEatMontage;
	UAnimMontage* PlayerPickUpMontage;

	// 保存当前播放的 Montage
	UAnimMontage* CurrentMontage;

	// 指定运行人称
	EGameViewMode::Type GameView;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		FRotator SpineRotator;
};
