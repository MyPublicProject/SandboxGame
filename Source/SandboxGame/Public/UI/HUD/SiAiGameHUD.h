// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSiAiGameHUDWidget.h"
#include "SiAiGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ASiAiGameHUD();

public:

	// 保存 GameMode
	class ASiAiGameMode* GM;

protected:

	virtual void BeginPlay() override;

private:

	TSharedPtr<class SSiAiGameHUDWidget> GameHUDWidget;
	
};
