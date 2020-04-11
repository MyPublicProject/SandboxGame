// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SiAiGameMode.generated.h"

// 初始化背包管理类委托
DECLARE_DELEGATE(FInitPackageManager)
/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ASiAiGameMode();

	virtual void Tick(float DeltaSeconds) override;

	// 组件赋值，给GameHUD调用，避免空引用引起的崩溃
	void InitGamePlayModule();

public:

	class ASiAiPlayerController *SPController;

	class ASiAiPlayerCharacter *SPCharacter;

	class ASiAiPlayerState *SPState;

	// 初始化背包管理委托,绑定的方法是PackageWidget的InitPackageManager方法
	FInitPackageManager InitPackageManager;

protected:

	virtual void BeginPlay() override;

	// 初始化背包管理类
	void InitializePackage();

private:

	// 是否已经初始化背包
	bool IsInitPackage;
	
	
};
