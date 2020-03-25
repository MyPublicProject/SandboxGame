// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiThirdPlayerAnim.h"
#include "Player/SiAiPlayerAnim.h"
#include "SiAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USiAiThirdPlayerAnim::USiAiThirdPlayerAnim()
{
	//������ֵ
	Direction = 0.f;
	//���Ƿ��ڿ��и�ֵ
	IsInAir = false;
}

void USiAiThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();
	if (!SPCharacter) return;
	// ��ȡ�Ƿ���Ծ
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;

	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;
}
