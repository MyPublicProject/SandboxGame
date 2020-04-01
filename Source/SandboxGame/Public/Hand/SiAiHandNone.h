// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SiAiHandObject.h"
#include "SiAiHandNone.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiHandNone : public ASiAiHandObject
{
	GENERATED_BODY()
	
public:

	ASiAiHandNone();

protected:
	
	virtual void BeginPlay() override;
	
};
