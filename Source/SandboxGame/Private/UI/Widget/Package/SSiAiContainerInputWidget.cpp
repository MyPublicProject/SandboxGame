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
	// �����Ƿ�ı�
	bool IsChanged = false;
	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;

	// ���ø����¼�
	SSiAiContainerBaseWidget::ResetContainerPara(ObjectID, Num);

	// ����иı�,��ִ�кϳ�����ί��
	if (IsChanged) CompoundInput.ExecuteIfBound();
}
