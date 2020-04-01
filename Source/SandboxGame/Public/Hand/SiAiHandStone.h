// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SiAiHandObject.h"
#include "SiAiHandStone.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiHandStone : public ASiAiHandObject
{
	GENERATED_BODY()
	
public:

	ASiAiHandStone();

protected:

	virtual void BeginPlay() override;
	
};
