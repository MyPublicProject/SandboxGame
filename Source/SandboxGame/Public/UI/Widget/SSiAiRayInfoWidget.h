// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"


class STextBlock;

DECLARE_DELEGATE_OneParam(FRegisterRayInfoEvent, TSharedPtr<STextBlock>)
/**
 * 
 */
class SANDBOXGAME_API SSiAiRayInfoWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiRayInfoWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

public:

	FRegisterRayInfoEvent RegisterRayInfoEvent;

private:

	//保存显示射线信息的文本
	TSharedPtr<STextBlock> RayInfoTextBlock;

	//获取GameStyle
	const struct FSiAiGameStyle *GameStyle;

	//是否已经初始化事件
	bool IsInitRayInfoEvent;

};
