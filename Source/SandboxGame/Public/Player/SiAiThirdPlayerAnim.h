// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SiAiPlayerAnim.h"
#include "SiAiThirdPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API USiAiThirdPlayerAnim : public USiAiPlayerAnim
{
	GENERATED_BODY()
	
public:

	USiAiThirdPlayerAnim();

protected:

	// 重写属性方法
	virtual void UpdateParameter() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Direction;
	
};
