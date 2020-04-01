// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerController.h"
#include "Player/SiAiPlayerCharacter.h"
#include "Player/SiAiPlayerState.h"




ASiAiPlayerController::ASiAiPlayerController()
{
	// 允许Tick
	PrimaryActorTick.bCanEverTick = true;
}

void ASiAiPlayerController::Tick(float DeltaSeconds)
{

}

void ASiAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// 绑定视角切换
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ASiAiPlayerController::ChangeView);
	// 绑定鼠标事件
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASiAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASiAiPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ASiAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ASiAiPlayerController::RightEventStop);
	// 绑定鼠标滚轮事件
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &ASiAiPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &ASiAiPlayerController::ScrollDownEvent);
}

void ASiAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!SPCharacter) SPCharacter = Cast<ASiAiPlayerCharacter>(GetCharacter());
	if (!SPState) SPState = Cast<ASiAiPlayerState>(PlayerState);
	// 设置鼠标不显示
	bShowMouseCursor = false;
	// 设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

	LeftUpperType = EUpperBody::PickUp;
	RightUpperType = EUpperBody::PickUp;

	IsRightButtonDown = false;
	IsLeftButtonDown = false;
}

void ASiAiPlayerController::ChangeView()
{
	//如果不允许切换视角,直接返回
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
	// 如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	// 如果鼠标有在按键不允许切换
	if (IsLeftButtonDown || IsRightButtonDown) return;

	// 告诉快捷栏切换快捷容器
	SPState->ChooseShortcut(true);
}

void ASiAiPlayerController::ScrollDownEvent()
{
	// 如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	// 如果鼠标有在按键不允许切换
	if (IsLeftButtonDown || IsRightButtonDown) return;

	// 告诉快捷栏切换快捷容器
	SPState->ChooseShortcut(false);
}
