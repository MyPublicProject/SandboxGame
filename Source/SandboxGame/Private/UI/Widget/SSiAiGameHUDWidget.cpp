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
#include "SImage.h"
#include "SSiAiGameMenuWidget.h"
#include "SSiAiChatRoomWidget.h"
#include "SSiAiPackageWidget.h"

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

			// 暗黑色遮罩,放在事件界面和游戏UI中间
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(BlackShade, SBorder)
				// 设置为褐色透明
				.ColorAndOpacity(TAttribute<FLinearColor>(FLinearColor(0.2f, 0.2f, 0.2f, 0.5f)))
				// 开始时设置不显示
				.Visibility(EVisibility::Hidden)
				[
					SNew(SImage)
				]
			]

			// GameMenu
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(GameMenuWidget, SSiAiGameMenuWidget)
				.Visibility(EVisibility::Hidden)
			]

			// ChatRoom
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ChatRoomWidget, SSiAiChatRoomWidget)
				.Visibility(EVisibility::Hidden)
			]

			//Package
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(PackageWidget, SSiAiPackageWidget)
				//设置DPI
				// .UIScaler(UIScaler)
				.Visibility(EVisibility::Hidden)
			]
		]
	];

	InitUIMap();

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSiAiGameHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

void SSiAiGameHUDWidget::ShowGameUI(EGameUIType::Type PrEUI, EGameUIType::Type NextUI)
{
	// 如果前一模式是Game,说明要显示黑板
	if (PrEUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Visible);
	}
	else
	{
		// 隐藏当前显示的UI
		UIMap.Find(PrEUI)->Get()->SetVisibility(EVisibility::Hidden);
	}
	// 如果下一模式是Game,隐藏黑板
	if (NextUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Hidden);
	}
	else
	{
		// 显示现在状态对应的UI
		UIMap.Find(NextUI)->Get()->SetVisibility(EVisibility::Visible);
		// 显示现在状态对应的UI
		// if (NextUI == EGameUIType::ChatRoom) ChatRoomWidget->ScrollToEnd();
		// 如果是失败,只显示一个按钮
		// if (NextUI == EGameUIType::Lose) GameMenuWidget->GameLose();
		// 如果是菜单,设置菜单初始化
		// if (NextUI == EGameUIType::Pause) GameMenuWidget->ResetMenu();
	}
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

void SSiAiGameHUDWidget::InitUIMap()
{
	UIMap.Add(EGameUIType::Pause, GameMenuWidget);
	UIMap.Add(EGameUIType::Package, PackageWidget);
	UIMap.Add(EGameUIType::ChatRoom, ChatRoomWidget);
	UIMap.Add(EGameUIType::Lose, GameMenuWidget);
}
