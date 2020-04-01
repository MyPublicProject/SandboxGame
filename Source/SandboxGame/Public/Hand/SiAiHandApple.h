// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SiAiHandObject.h"
#include "SiAiHandApple.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiHandApple : public ASiAiHandObject
{
	GENERATED_BODY()
	
public:

	ASiAiHandApple();

protected:
	
	virtual void BeginPlay() override;
	
};
