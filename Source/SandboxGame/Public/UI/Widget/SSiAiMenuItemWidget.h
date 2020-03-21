// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"


// 委托
DECLARE_DELEGATE_OneParam(FItemClicked, const EMenuItem::Type)

/**
 * 
 */
class SANDBOXGAME_API SSiAiMenuItemWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiMenuItemWidget)
	{}

	SLATE_ATTRIBUTE(FText, ItemText)

	SLATE_EVENT(FItemClicked, OnClicked)

	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// 重写按钮 OnMouseButtonDown 方法
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	// 重写按钮 OnMouseButtonUp 方法
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	// 重写按钮 OnMouseLeave 方法
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

private:

	// 获取颜色
	FSlateColor GetTintColor() const;

private:

	// 获取 MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;

	// 按下事件委托
	FItemClicked OnClicked;

	EMenuItem::Type ItemType;

	// 按钮是否已经按下
	bool IsMouseButtonDown;

};
