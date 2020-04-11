// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiContainerInputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiContainerInputWidget::Construct(const FArguments& InArgs)
{
	SSiAiContainerBaseWidget::Construct(
		SSiAiContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiContainerInputWidget::ResetContainerPara(int ObjectID, int Num)
{
	// 定义是否改变
	bool IsChanged = false;
	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;

	// 调用父类事件
	SSiAiContainerBaseWidget::ResetContainerPara(ObjectID, Num);

	// 如果有改变,就执行合成输入委托
	if (IsChanged) CompoundInput.ExecuteIfBound();
}
