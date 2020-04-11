// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSiAiContainerBaseWidget.h"
#include "DeclarativeSyntaxSupport.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiContainerShortcutWidget : public SSiAiContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiContainerShortcutWidget)
	{}
	SLATE_ATTRIBUTE(int, WorkIndex)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
