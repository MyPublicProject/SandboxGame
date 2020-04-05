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

	// �����͹ر�������Ʒ�Ľ������
	UFUNCTION(BlueprintCallable, Category = "SiAi")
		void ChangeDetection(bool IsOpen);

	// �����͹ر�������Ʒ����ʾ���,�ڼ�����ʱ�����
	UFUNCTION(BlueprintCallable, Category = PlayAnim)
		void RenderHandObject(bool IsRender);

protected:

	// ��ȡ��ɫָ��
	void InitSPCharacter();

	// ��������
	virtual void UpdateParameter();

	// ���¶���
	virtual void UpdateMontage();

	// �Ƿ������л��ӽ�
	void AllowViewChange(bool IsAllow);

protected:

	//��ɫָ��
	class ASiAiPlayerCharacter* SPCharacter;

	//�ϰ����Montage
	UAnimMontage* PlayerHitMontage;
	UAnimMontage* PlayerFightMontage;
	UAnimMontage* PlayerPunchMontage;
	UAnimMontage* PlayerEatMontage;
	UAnimMontage* PlayerPickUpMontage;

	// ���浱ǰ���ŵ� Montage
	UAnimMontage* CurrentMontage;

	// ָ�������˳�
	EGameViewMode::Type GameView;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		FRotator SpineRotator;
};
