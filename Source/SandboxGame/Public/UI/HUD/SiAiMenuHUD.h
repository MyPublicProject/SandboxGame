// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SiAiMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ASiAiMenuHUD();

	TSharedPtr<class SSiAiMeunHUDWidget> MenuHUDWidget;
	
};
