// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	// 保存根节点
	TSharedPtr<SBox> RootSizeBox;
	// 获取 MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;
	// 保存标题
	TSharedPtr<STextBlock> TitleText;

};
