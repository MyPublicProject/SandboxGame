// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiPlayerStateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiPlayerStateWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// 更新状态事件，绑定委托 PlayerState 的 UpstateStateWidget
	void UpdateStateWidget(float HPValue, float HungerValue);

private:

	// 获取GameStyle
	const struct FSiAiGameStyle *GameStyle;

	// 血条
	TSharedPtr<class SProgressBar> HPBar;

	// 解饿度
	TSharedPtr<SProgressBar> HungerBar;

};
