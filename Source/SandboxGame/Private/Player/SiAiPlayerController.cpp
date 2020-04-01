// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerController.h"
#include "Player/SiAiPlayerCharacter.h"
#include "Player/SiAiPlayerState.h"
#include "SiAiMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "SiAiHelper.h"


ASiAiPlayerController::ASiAiPlayerController()
{
	// 允许Tick
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
	// 退出游戏
	InputComponent->BindAction("QuitGame", IE_Pressed, this, &ASiAiPlayerController::QuitGame);
}

void ASiAiPlayerController::ChangeHandObject()
{
	// 切换手持物品
	SPCharacter->ChangeHandObject(SPState->GetCurrentHandObjectIndex());
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

// 	LeftUpperType = EUpperBody::PickUp;
// 	RightUpperType = EUpperBody::PickUp;

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

	//更改Character的手持物品
	ChangeHandObject();
}

void ASiAiPlayerController::ScrollDownEvent()
{
	// 如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	// 如果鼠标有在按键不允许切换
	if (IsLeftButtonDown || IsRightButtonDown) return;

	// 告诉快捷栏切换快捷容器
	SPState->ChooseShortcut(false);

	//更改Character的手持物品
	ChangeHandObject();
}

void ASiAiPlayerController::QuitGame()
{
	// 控制台
	Cast<ASiAiMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
}

void ASiAiPlayerController::ChangePreUpperType(EUpperBody::Type RightType = EUpperBody::None)
{
	//根据当前手持物品的类型来修改预动作
	switch (SPState->GetCurrentObjectType())
	{
	case EObjectType::Normal:
		LeftUpperType = EUpperBody::Punch;
		RightUpperType = RightType;
		break;
	case EObjectType::Food:
		LeftUpperType = EUpperBody::Punch;
		//如果右键状态是拾取那就给拾取,拾取优先级高
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