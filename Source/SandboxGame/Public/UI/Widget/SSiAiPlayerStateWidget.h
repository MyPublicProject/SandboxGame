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

	// ����״̬�¼�����ί�� PlayerState �� UpstateStateWidget
	void UpdateStateWidget(float HPValue, float HungerValue);

private:

	// ��ȡGameStyle
	const struct FSiAiGameStyle *GameStyle;

	// Ѫ��
	TSharedPtr<class SProgressBar> HPBar;

	// �����
	TSharedPtr<SProgressBar> HungerBar;

};
