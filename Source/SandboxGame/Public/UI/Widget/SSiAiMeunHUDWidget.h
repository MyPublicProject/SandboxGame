// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiMeunHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiMeunHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	// 绑定 UIScaler 的函数
	float GetUIScaler() const;
	// 获取屏幕尺寸
	FVector2D GetViewportSize() const;

	// FReply OnClick();

private:

	// 获取 Menu 样式
	const struct FSiAiMenuStyle *MenuStyle;

	// DPI 缩放参数
	TAttribute<float> UIScaler;

	// 获取Image的Slot
	// SOverlay::FOverlaySlot *ImageSlot;

	// 菜单指针
	TSharedPtr<class SSiAiMenuWidget> MenuWidget;
};
