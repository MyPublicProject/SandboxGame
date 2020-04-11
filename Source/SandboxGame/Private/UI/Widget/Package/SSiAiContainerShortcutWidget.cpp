// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiContainerShortcutWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiContainerShortcutWidget::Construct(const FArguments& InArgs)
{
	SSiAiContainerBaseWidget::Construct(
		SSiAiContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiContainerShortcutWidget::ResetContainerPara(int ObjectID, int Num)
{
	//�����Ƿ�ı�
	bool IsChanged = false;
	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;

	//���ø����¼�
	SSiAiContainerBaseWidget::ResetContainerPara(ObjectID, Num);


	//����иı�, ִ�п�����޸ĸ���ί��,�������������Լ��µ���ƷID
	if (IsChanged) PackShortChange.ExecuteIfBound(WorkIndex.Get(), ObjectID, Num);
}
