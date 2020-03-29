// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SiAiGameMode.generated.h"

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

protected:

	virtual void BeginPlay() override;
	
	
};
