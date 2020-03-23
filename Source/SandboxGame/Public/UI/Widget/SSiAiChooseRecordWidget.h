// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class STextComboBox;

/**
 * 
 */
class SANDBOXGAME_API SSiAiChooseRecordWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiChooseRecordWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// ���´浵��
	void UpdataRecordName();

private:

	// ��ȡ MenusStyle
	const struct FSiAiMenuStyle *MenuStyle;
	// �����˵�
	TSharedPtr<STextComboBox> RecordComboBox;
	// �ַ���ָ������
	TArray<TSharedPtr<FString>> OptionsSource;

};
