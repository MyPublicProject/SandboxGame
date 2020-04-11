// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSiAiContainerBaseWidget.h"
#include "DeclarativeSyntaxSupport.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiContainerInputWidget : public SSiAiContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiContainerInputWidget)
	{}
	SLATE_ATTRIBUTE(int, WorkIndex)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void ResetContainerPara(int ObjectID, int Num) override;
};
