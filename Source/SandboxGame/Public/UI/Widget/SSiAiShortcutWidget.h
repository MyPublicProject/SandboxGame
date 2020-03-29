// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"
#include "STextBlock.h"

// 注册快捷栏到 PlayerState 的委托
DECLARE_DELEGATE_TwoParams(FRegisterShortcutContainer, TArray<TSharedPtr<ShortcutContainer>>*, TSharedPtr<STextBlock>)


/**
 * 
 */
class SANDBOXGAME_API SSiAiShortcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiShortcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

public:

	FRegisterShortcutContainer RegisterShortcutContainer;

private:

	// 初始化所有容器
	void InitializeContainer();

private:

	// 获取 GameStyle 
	const struct  FSiAiGameStyle *GameStyle;

	// 物品信息文本
	TSharedPtr<STextBlock> ShortcutInfoTextBlock;

	//网格指针
	TSharedPtr<class SUniformGridPanel> GridPanel;

	// 是否初始化容器
	bool IsInitializeContainer;
};
