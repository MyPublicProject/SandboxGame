// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SiAiHandObject.h"
#include "SiAiHandHammer.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiHandHammer : public ASiAiHandObject
{
	GENERATED_BODY()
	
public:

	ASiAiHandHammer();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* ExtendMesh;
	
};
