// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiMenuController.h"




ASiAiMenuController::ASiAiMenuController()
{
	bShowMouseCursor = true;
}

void ASiAiMenuController::BeginPlay()
{
	// �������ģʽ
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}
