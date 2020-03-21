// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiGameOptionWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	// ͳһ������ʽ
	void StyleInitialize();
	// ���� CheckBox �¼�
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	// Ӣ�� CheckBox �¼�
	void EnCheckBoxStateChanged(ECheckBoxState NewState);

private:

	// ��ȡ MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;

	// ��ȡ CheckBox ָ��
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;
};
