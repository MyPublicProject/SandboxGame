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

protected:

	virtual void BeginPlay() override;
	
	
};
