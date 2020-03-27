// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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

private:

	TSharedPtr<class SSiAiGameHUDWidget> GameHUDWidget;
	
};
