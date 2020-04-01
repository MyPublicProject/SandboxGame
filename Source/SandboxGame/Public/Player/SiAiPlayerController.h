// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AiSiTypes.h"
#include "SiAiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ASiAiPlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

protected:

	//��ɫָ��
	class ASiAiPlayerCharacter *SPCharacter;

	class ASiAiPlayerState *SPState;

protected:

	virtual void BeginPlay() override;

private:

	// �л��ӽ�
	void ChangeView();

	// ��갴���¼�
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();

	// �������¼�
	void ScrollUpEvent();
	void ScrollDownEvent();

private:

	//���Ԥ����
	EUpperBody::Type LeftUpperType;

	//�Ҽ�Ԥ����
	EUpperBody::Type RightUpperType;

	//�Ƿ�ס��������
	bool IsLeftButtonDown;
	bool IsRightButtonDown;
	
};
