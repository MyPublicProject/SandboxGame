// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerAnim.h"
#include "Player/SiAiPlayerAnim.h"
#include "SiAiPlayerCharacter.h"
#include "AiSiTypes.h"

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

	// 当前人称状态和动作
	if (SPCharacter->GameView != GameView) return;

	// 当前动作没有停止，不更新动作
	if (!Montage_GetIsStopped(CurrentMontage)) return;
	
	switch (SPCharacter->UpperType)
	{
	case EUpperBody::None:
		if (CurrentMontage != nullptr)
		{
			// 停止所有的蒙太奇动作
			Montage_Stop(0);
			CurrentMontage = nullptr;
			AllowViewChange(true);
		}
		break;
	case EUpperBody::Punch:
		if (!Montage_IsPlaying(PlayerPunchMontage)) {
			Montage_Play(PlayerPunchMontage);
			CurrentMontage = PlayerPunchMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Hit:
		if (!Montage_IsPlaying(PlayerHitMontage)) {
			Montage_Play(PlayerHitMontage);
			CurrentMontage = PlayerHitMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Fight:
		if (!Montage_IsPlaying(PlayerFightMontage)) {
			Montage_Play(PlayerFightMontage);
			CurrentMontage = PlayerFightMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::PickUp:
		if (!Montage_IsPlaying(PlayerPickUpMontage)) {
			Montage_Play(PlayerPickUpMontage);
			CurrentMontage = PlayerPickUpMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Eat:
		if (!Montage_IsPlaying(PlayerEatMontage)) {
			Montage_Play(PlayerEatMontage);
			CurrentMontage = PlayerEatMontage;
			AllowViewChange(false);
		}
		break;
	}
}

void USiAiPlayerAnim::AllowViewChange(bool IsAllow)
{
	if (!SPCharacter)return;
	SPCharacter->IsAllowSwitch = IsAllow;
}
