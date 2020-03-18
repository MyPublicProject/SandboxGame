// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SiAiMenuController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ASiAiMenuController();

protected:

	virtual void BeginPlay() override;
		
};
