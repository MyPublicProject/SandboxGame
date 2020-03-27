// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiShortcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiShortcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:

	// ��ʼ����������
	void InitializeContainer();

private:

	// ��ȡ GameStyle 
	const struct  FSiAiGameStyle *GameStyle;

	// ��Ʒ��Ϣ�ı�
	TSharedPtr<STextBlock> ShortcutInfoTextBlock;

	//����ָ��
	TSharedPtr<class SUniformGridPanel> GridPanel;

	// �Ƿ��ʼ������
	bool IsInitializeContainer;
};
