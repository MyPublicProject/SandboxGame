// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "SSiAiShortcutWidget.h"
#include "SDPIScaler.h"
#include "SOverlay.h"
#include "SSiAiShortcutWidget.h"
#include "SSiAiRayInfoWidget.h"
#include "Engine/GameViewportClient.h"
#include "SSiAiPointerWidget.h"
#include "SSiAiPlayerStateWidget.h"

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

			// 快捷栏
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShortcutWidget, SSiAiShortcutWidget)
			]

			// 射线信息
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(RayInfoWidget, SSiAiRayInfoWidget)
			]

			// 准星
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(PointerWidget, SSiAiPointerWidget)
			]

			// 玩家状态
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SAssignNew(PlayerStateWidget, SSiAiPlayerStateWidget)
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
