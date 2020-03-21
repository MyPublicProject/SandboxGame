// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiGameOptionWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	// 统一设置样式
	void StyleInitialize();
	// 中文 CheckBox 事件
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	// 英文 CheckBox 事件
	void EnCheckBoxStateChanged(ECheckBoxState NewState);

private:

	// 获取 MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;

	// 获取 CheckBox 指针
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;
};
