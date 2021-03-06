// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiGameMode.h"
#include "SiAiGameHUD.h"
#include "Player/SiAiPlayerState.h"
#include "Player/SiAiPlayerCharacter.h"
#include "Player/SiAiPlayerController.h"
#include "SlAiDataHandle.h"
#include "Kismet/GameplayStatics.h"
#include "SiAiPackageManager.h"




ASiAiGameMode::ASiAiGameMode()
{
	// 允许开启 Tick 函数
	PrimaryActorTick.bCanEverTick = true;

	// 添加组件
	HUDClass = ASiAiGameHUD::StaticClass();
	PlayerControllerClass = ASiAiPlayerController::StaticClass();
	PlayerStateClass = ASiAiPlayerState::StaticClass();
	DefaultPawnClass = ASiAiPlayerCharacter::StaticClass();

	// 开始没有初始化背包
	IsInitPackage = false;
}

void ASiAiGameMode::Tick(float DeltaSeconds)
{
	InitializePackage();
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
	Super::BeginPlay();

	if (!SPController) InitGamePlayModule();

	// 初始化游戏数据
	SlAiDataHandle::Get()->InitializeGameData();
}

void ASiAiGameMode::InitializePackage()
{
	if (IsInitPackage) return;

	// 叫PackageWidget初始化背包管理器
	InitPackageManager.ExecuteIfBound();
	// 绑定丢弃物品属性
	SiAiPackageManager::Get()->PlayerThrowObject.BindUObject(SPCharacter, &ASiAiPlayerCharacter::PlayerThrowObject);
	// 绑定修改快捷栏信息
	SiAiPackageManager::Get()->ChangeHandObject.BindUObject(SPState, &ASiAiPlayerState::ChangeHandObject);
	IsInitPackage = true;
}
