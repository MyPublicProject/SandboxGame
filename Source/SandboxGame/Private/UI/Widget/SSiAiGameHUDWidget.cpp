// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "SSiAiShortcutWidget.h"
#include "SDPIScaler.h"
#include "SOverlay.h"
#include "SSiAiShortcutWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiGameHUDWidget::Construct(const FArguments& InArgs)
{
	UIScaler.Bind(this, &SSiAiGameHUDWidget::GetUIScaler);
	ChildSlot
	[
		SNew(SDPIScaler)
		.DPIScale(UIScaler)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShortcutWidget, SSiAiShortcutWidget)
			]
		]
	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSiAiGameHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

FVector2D SSiAiGameHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920.f, 1080.f);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}