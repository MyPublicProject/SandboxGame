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

	// 更新存档名
	void UpdataRecordName();

private:

	// 获取 MenusStyle
	const struct FSiAiMenuStyle *MenuStyle;
	// 下拉菜单
	TSharedPtr<STextComboBox> RecordComboBox;
	// 字符串指针数组
	TArray<TSharedPtr<FString>> OptionsSource;

};
