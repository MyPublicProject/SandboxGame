// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SiAiHandObject.h"
#include "SiAiHandSword.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiHandSword : public ASiAiHandObject
{
	GENERATED_BODY()
	
public:

	ASiAiHandSword();

protected:
	
	virtual void BeginPlay() override;
	
};
