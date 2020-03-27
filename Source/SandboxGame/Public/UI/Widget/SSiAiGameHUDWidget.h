// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiGameHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiGameHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// 绑定到 UIScaler的方法
	float GetUIScaler() const;

public:

	// 快捷栏
	TSharedPtr<class SSiAiShortcutWidget> ShortcutWidget;

private:

	// 获取屏幕大小
	FVector2D GetViewportSize() const;

private:

	// DPI 缩放
	TAttribute<float> UIScaler;
};
