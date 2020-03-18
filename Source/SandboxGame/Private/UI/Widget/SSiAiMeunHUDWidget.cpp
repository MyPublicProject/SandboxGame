// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiMeunHUDWidget.h"
#include "SlateOptMacros.h"
#include "SImage.h"
#include "SiAiStyle.h"
#include "SiAiMenuWidgetStyle.h"
#include "SOverlay.h"
#include "Engine/Engine.h"
#include "SDPIScaler.h"
#include "SButton.h"
#include "SSiAiMenuWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiMeunHUDWidget::Construct(const FArguments& InArgs)
{
	// 获取编辑器的 MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");
	// 绑定 UIScaler 
	UIScaler.Bind(this, &SSiAiMeunHUDWidget::GetUIScaler);
	ChildSlot
		[
			SNew(SDPIScaler)
			.DPIScale(UIScaler)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&MenuStyle->MenuHUDBackgroundBrush)
				]
				/*
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Expose(ImageSlot)
				[
					SNew(SImage)
					.Image(&MenuStyle->MenuBackgroundBrush)
				]
				*/
				+ SOverlay::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				[
					SAssignNew(MenuWidget, SSiAiMenuWidget)
				]
			]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSiAiMeunHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.0f;
}

FVector2D SSiAiMeunHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920, 1080);
	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(Result);
		return Result;
}

/*
FReply SSiAiMeunHUDWidget::OnClick()
{
	ImageSlot->HAlign(HAlign_Right).VAlign(VAlign_Top);
	return FReply::Handled();
}
}*/
