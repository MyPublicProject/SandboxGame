// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiChatRoomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiChatRoomWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
