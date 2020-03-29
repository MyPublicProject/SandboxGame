// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiGameMode.h"
#include "SiAiGameHUD.h"
#include "Player/SiAiPlayerState.h"
#include "Player/SiAiPlayerCharacter.h"
#include "Player/SiAiPlayerController.h"
#include "SlAiDataHandle.h"
#include "Kismet/GameplayStatics.h"




ASiAiGameMode::ASiAiGameMode()
{
	// 允许开启 Tick 函数
	PrimaryActorTick.bCanEverTick = true;

	// 添加组件
	HUDClass = ASiAiGameHUD::StaticClass();
	PlayerControllerClass = ASiAiPlayerController::StaticClass();
	PlayerStateClass = ASiAiPlayerState::StaticClass();
	DefaultPawnClass = ASiAiPlayerCharacter::StaticClass();
}

void ASiAiGameMode::Tick(float DeltaSeconds)
{

}

void ASiAiGameMode::InitGamePlayModule()
{
	// 添加引用
	SPController = Cast<ASiAiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	SPCharacter = Cast<ASiAiPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SPState = Cast<ASiAiPlayerState>(SPController->PlayerState);
}

void ASiAiGameMode::BeginPlay()
{
	// 初始化游戏数据
	SlAiDataHandle::Get()->InitializeGameData();

	if (!SPController) InitGamePlayModule();
}
