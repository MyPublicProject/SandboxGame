// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiMeunHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiMeunHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	// �� UIScaler �ĺ���
	float GetUIScaler() const;
	// ��ȡ��Ļ�ߴ�
	FVector2D GetViewportSize() const;

	// FReply OnClick();

private:

	// ��ȡ Menu ��ʽ
	const struct FSiAiMenuStyle *MenuStyle;

	// DPI ���Ų���
	TAttribute<float> UIScaler;

	// ��ȡImage��Slot
	// SOverlay::FOverlaySlot *ImageSlot;

	// �˵�ָ��
	TSharedPtr<class SSiAiMenuWidget> MenuWidget;
};
