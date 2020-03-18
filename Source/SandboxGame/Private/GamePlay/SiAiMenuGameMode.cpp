// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiMenuGameMode.h"
#include "SiAiMenuHUD.h"
#include "SiAiMenuController.h"



ASiAiMenuGameMode::ASiAiMenuGameMode()
{
	PlayerControllerClass = ASiAiMenuController::StaticClass();
	HUDClass = ASiAiMenuHUD::StaticClass();
}
