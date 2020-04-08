// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"
#include "AiSiTypes.h"

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

	// 显示游戏 UI，被 PlayerController 的 ShowGameUI 委托绑定
	void ShowGameUI(EGameUIType::Type PrEUI, EGameUIType::Type NextUI);

public:

	// 快捷栏
	TSharedPtr<class SSiAiShortcutWidget> ShortcutWidget;

	// 射线信息框
	TSharedPtr<class SSiAiRayInfoWidget> RayInfoWidget;

	// 准星
	TSharedPtr<class SSiAiPointerWidget> PointerWidget;

	// 玩家状态
	TSharedPtr<class SSiAiPlayerStateWidget> PlayerStateWidget;

	// 游戏菜单
	TSharedPtr<class SSiAiGameMenuWidget> GameMenuWidget;

	// 聊天室
	TSharedPtr<class SSiAiChatRoomWidget> ChatRoomWidget;

	// 背包
	TSharedPtr<class SSiAiPackageWidget> PackageWidget;

private:

	// 获取屏幕大小
	FVector2D GetViewportSize() const;

	// 将 UI 绑定到 UIMap
	void InitUIMap();

private:

	// DPI 缩放
	TAttribute<float> UIScaler;

	// 褐色遮罩
	TSharedPtr<class SBorder> BlackShade;

	// UIMap
	TMap<EGameUIType::Type, TSharedPtr<SCompoundWidget>> UIMap;

};
