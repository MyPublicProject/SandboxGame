// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

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

	// �󶨵� UIScaler�ķ���
	float GetUIScaler() const;

public:

	// �����
	TSharedPtr<class SSiAiShortcutWidget> ShortcutWidget;

private:

	// ��ȡ��Ļ��С
	FVector2D GetViewportSize() const;

private:

	// DPI ����
	TAttribute<float> UIScaler;
};
