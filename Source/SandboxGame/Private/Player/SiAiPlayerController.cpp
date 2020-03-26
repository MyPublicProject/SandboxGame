// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerController.h"
#include "Player/SiAiPlayerCharacter.h"




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
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASiAiPlayerController::RightEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASiAiPlayerController::RightEventStop);
}

void ASiAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!SPCharacter) SPCharacter = Cast<ASiAiPlayerCharacter>(GetCharacter());
	// 设置鼠标不显示
	bShowMouseCursor = false;
	// 设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);
}

void ASiAiPlayerController::ChangeView()
{
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

}

void ASiAiPlayerController::LeftEventStop()
{

}

void ASiAiPlayerController::RightEventStart()
{

}

void ASiAiPlayerController::RightEventStop()
{

}
