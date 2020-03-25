// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiGameMode.h"
#include "SiAiGameHUD.h"
#include "Player/SiAiPlayerState.h"
#include "Player/SiAiPlayerCharacter.h"
#include "Player/SiAiPlayerController.h"




ASiAiGameMode::ASiAiGameMode()
{
	// �������� Tick ����
	PrimaryActorTick.bCanEverTick = true;

	// �������
	HUDClass = ASiAiGameHUD::StaticClass();
	PlayerControllerClass = ASiAiPlayerController::StaticClass();
	PlayerStateClass = ASiAiPlayerState::StaticClass();
	DefaultPawnClass = ASiAiPlayerCharacter::StaticClass();
}

void ASiAiGameMode::Tick(float DeltaSeconds)
{

}

void ASiAiGameMode::BeginPlay()
{

}