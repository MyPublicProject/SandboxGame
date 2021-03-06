// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

class SBorder;
class SUniformGridPanel;

/**
 * 
 */
class SANDBOXGAME_API SSiAiPackageWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiPackageWidget)
	{}
	SLATE_ATTRIBUTE(float, UIScaler)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	// 重写绘制函数
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
	// 重写鼠标点击事件
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	
	// 注册背包管理器事件，由 PlayerCharacter 的 InitPackageManager 委托进行调用
	void InitPackageManager();

private:

	// 获取 MenuStyle
	const struct FSiAiGameStyle * GameStyle;

	// 快捷栏表格
	TSharedPtr<SUniformGridPanel> ShortcutGrid;

	// 背包表格
	TSharedPtr<SUniformGridPanel> PackageGrid;

	// 合成表表格
	TSharedPtr<SUniformGridPanel> CompoundGrid;

	// 输出容器
	TSharedPtr<SBorder> OutputBorder;

	// 鼠标位置标定
	FVector2D MousePosition;

	// DPI的缩放
	TAttribute<float> UIScaler;

	// 是否已经初始化背包管理器
	bool IsInitPackageMana;

};
