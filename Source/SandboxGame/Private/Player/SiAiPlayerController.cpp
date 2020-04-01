// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerController.h"
#include "Player/SiAiPlayerCharacter.h"
#include "Player/SiAiPlayerState.h"
#include "SiAiMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "SiAiHelper.h"


ASiAiPlayerController::ASiAiPlayerController()
{
	// ����Tick
	PrimaryActorTick.bCanEverTick = true;
}

void ASiAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ChangePreUpperType(EUpperBody::None);
}

void ASiAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// ���ӽ��л�
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ASiAiPlayerController::ChangeView);
	// ������¼�
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASiAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASiAiPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ASiAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ASiAiPlayerController::RightEventStop);
	// ���������¼�
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &ASiAiPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &ASiAiPlayerController::ScrollDownEvent);
	// �˳���Ϸ
	InputComponent->BindAction("QuitGame", IE_Pressed, this, &ASiAiPlayerController::QuitGame);
}

void ASiAiPlayerController::ChangeHandObject()
{
	// �л��ֳ���Ʒ
	SPCharacter->ChangeHandObject(SPState->GetCurrentHandObjectIndex());
}

void ASiAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!SPCharacter) SPCharacter = Cast<ASiAiPlayerCharacter>(GetCharacter());
	if (!SPState) SPState = Cast<ASiAiPlayerState>(PlayerState);
	// ������겻��ʾ
	bShowMouseCursor = false;
	// ��������ģʽ
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

// 	LeftUpperType = EUpperBody::PickUp;
// 	RightUpperType = EUpperBody::PickUp;

	IsRightButtonDown = false;
	IsLeftButtonDown = false;
}

void ASiAiPlayerController::ChangeView()
{
	//����������л��ӽ�,ֱ�ӷ���
	if (!SPCharacter->IsAllowSwitch) return;

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		SPCharacter->ChangeView(EGameViewMode::Third);
		break;
	case EGameViewMode::Third:
		SPCharacter->ChangeView(EGameViewMode::First);
		break;
	default:
		break;
	}
}

void ASiAiPlayerController::LeftEventStart()
{
	IsLeftButtonDown = true;
	SPCharacter->UpperType = LeftUpperType;
}

void ASiAiPlayerController::LeftEventStop()
{
	IsLeftButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASiAiPlayerController::RightEventStart()
{
	IsRightButtonDown = true;
	SPCharacter->UpperType = RightUpperType;
}

void ASiAiPlayerController::RightEventStop()
{
	IsRightButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASiAiPlayerController::ScrollUpEvent()
{
	// ����������л�ֱ�ӷ���
	if (!SPCharacter->IsAllowSwitch) return;

	// ���������ڰ����������л�
	if (IsLeftButtonDown || IsRightButtonDown) return;

	// ���߿�����л��������
	SPState->ChooseShortcut(true);

	//����Character���ֳ���Ʒ
	ChangeHandObject();
}

void ASiAiPlayerController::ScrollDownEvent()
{
	// ����������л�ֱ�ӷ���
	if (!SPCharacter->IsAllowSwitch) return;

	// ���������ڰ����������л�
	if (IsLeftButtonDown || IsRightButtonDown) return;

	// ���߿�����л��������
	SPState->ChooseShortcut(false);

	//����Character���ֳ���Ʒ
	ChangeHandObject();
}

void ASiAiPlayerController::QuitGame()
{
	// ����̨
	Cast<ASiAiMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
}

void ASiAiPlayerController::ChangePreUpperType(EUpperBody::Type RightType = EUpperBody::None)
{
	//���ݵ�ǰ�ֳ���Ʒ���������޸�Ԥ����
	switch (SPState->GetCurrentObjectType())
	{
	case EObjectType::Normal:
		LeftUpperType = EUpperBody::Punch;
		RightUpperType = RightType;
		break;
	case EObjectType::Food:
		LeftUpperType = EUpperBody::Punch;
		//����Ҽ�״̬��ʰȡ�Ǿ͸�ʰȡ,ʰȡ���ȼ���
		RightUpperType = RightType == EUpperBody::None ? EUpperBody::Eat : RightType;
		break;
	case EObjectType::Tool:
		LeftUpperType = EUpperBody::Hit;
		RightUpperType = RightType;
		break;
	case EObjectType::Weapon:
		LeftUpperType = EUpperBody::Fight;
		RightUpperType = RightType;
		break;
	}
	SiAiHelper::Debug("LeftUpperType", 0.f);
}