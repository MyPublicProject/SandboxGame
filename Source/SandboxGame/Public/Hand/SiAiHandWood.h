// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SiAiHandObject.h"
#include "SiAiHandWood.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiHandWood : public ASiAiHandObject
{
	GENERATED_BODY()
	
public:

	ASiAiHandWood();
	
protected:

	virtual void BeginPlay() override;
	
};
