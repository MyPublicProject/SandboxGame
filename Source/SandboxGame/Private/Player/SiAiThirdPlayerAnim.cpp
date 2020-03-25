// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiThirdPlayerAnim.h"
#include "Player/SiAiPlayerAnim.h"
#include "SiAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USiAiThirdPlayerAnim::USiAiThirdPlayerAnim()
{
	//给方向赋值
	Direction = 0.f;
	//给是否在空中赋值
	IsInAir = false;
}

void USiAiThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();
	if (!SPCharacter) return;
	// 获取是否跳跃
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;

	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;
}
