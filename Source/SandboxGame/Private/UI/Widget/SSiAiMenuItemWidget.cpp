// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiMenuItemWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SImage.h"
#include "STextBlock.h"
#include "SiAiMenuWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiMenuItemWidget::Construct(const FArguments& InArgs)
{
	// InArgs 可以获取到传过来的数值
	OnClicked = InArgs._OnClicked;
	ItemType = InArgs._ItemType.Get();

	// 获取编辑器的 MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
				.ColorAndOpacity(this, &SSiAiMenuItemWidget::GetTintColor)
			]

			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(InArgs._ItemText)
				.Font(MenuStyle->Font_60)
			]
		]
	];

	// 初始化
	IsMouseButtonDown = false;

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SSiAiMenuItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = true;
	return FReply::Handled();
}

FReply SSiAiMenuItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (IsMouseButtonDown)
	{
		IsMouseButtonDown = false;
		OnClicked.ExecuteIfBound(ItemType);
	}
	return FReply::Handled();
}

void SSiAiMenuItemWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = false;
}

FSlateColor SSiAiMenuItemWidget::GetTintColor() const
{
	if (IsMouseButtonDown) return FLinearColor(1.f, 0.1f, 0.1f, 0.5f);
	return FLinearColor(1.f, 1.f, 1.f, 1.f);
}
