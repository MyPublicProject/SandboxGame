// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerAnim.h"
#include "Player/SiAiPlayerAnim.h"
#include "SiAiPlayerCharacter.h"

USiAiPlayerAnim::USiAiPlayerAnim()
{
	Speed = 0.f;
	SpineRotator = FRotator(0.f, 0.f, 0.f);
}

void USiAiPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	InitSPCharacter();
	UpdateParameter();
	UpdateMontage();
}

void USiAiPlayerAnim::InitSPCharacter()
{
	if (!SPCharacter)
	{
		SPCharacter = Cast<ASiAiPlayerCharacter>(TryGetPawnOwner());
	}
}

void USiAiPlayerAnim::UpdateParameter()
{
	if (!SPCharacter) return;
	// 设置速度
	Speed = SPCharacter->GetVelocity().Size();
	// 定义上半身的旋转
	float SpineDir = SPCharacter->GetActorRotation().Yaw - 90.f;
	if (SpineDir > 180.f) SpineDir -= 360.f;
	if (SpineDir < -180.f) SpineDir += 360.f;
	SpineRotator = FRotator(0.f, SpineDir, 90.f);
}

void USiAiPlayerAnim::UpdateMontage()
{
	if (!SPCharacter) return;
	if (!Montage_IsPlaying(PlayerPunchMontage))
	{
		Montage_Play(PlayerPunchMontage);
	}
}
