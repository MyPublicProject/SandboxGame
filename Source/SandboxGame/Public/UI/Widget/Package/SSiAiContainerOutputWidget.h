// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSiAiContainerBaseWidget.h"
#include "DeclarativeSyntaxSupport.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiContainerOutputWidget : public SSiAiContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiContainerOutputWidget)
	{}
	SLATE_ATTRIBUTE(int, WorkIndex)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// 重写左键操作
	virtual void LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum) override;

	// 重些右键操作
	virtual void RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum) override;
};
