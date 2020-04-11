// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiContainerOutputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiContainerOutputWidget::Construct(const FArguments& InArgs)
{
	SSiAiContainerBaseWidget::Construct(
		SSiAiContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiContainerOutputWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	// ���������ƷΪ�գ�ֱ�ӷ��� return
	if (ObjectIndex == 0)
	{
		OutputID = InputID;
		OutputNum = InputNum;
		return;
	}

	// ����������Ʒ��Ϊ��״̬
	if (InputID == ObjectIndex && MultiplyAble(InputID))
	{
		OutputID = ObjectIndex;
		OutputNum = (InputNum + ObjectNum <= 64) ? (InputNum + ObjectNum) : 64;
		ObjectNum = (InputNum + ObjectNum <= 64) ? 0 : (InputNum + ObjectNum - 64);
		// ִ�кϳ����ί��
		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);
		return;
	}

	// �����Ʒ����ͬ������Ʒ��ͬ���ǲ��ܵ���,�����Ʒ,����������Ʒ
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	// ִ�кϳ����ί��
	CompoundOutput.ExecuteIfBound(ObjectIndex, ObjectNum);
	// ִ�ж�����Ʒί��
	ThrowObject.ExecuteIfBound(InputID, InputNum);

}

void SSiAiContainerOutputWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	// ���������ƷΪ0
	if (ObjectIndex == 0) {
		OutputID = InputID;
		OutputNum = InputNum;
		return;
	}

	// �������Ϊ��,ֱ�Ӹ������ص�һ��
	if (InputID == 0) {
		OutputID = ObjectIndex;
		// ������˫��
		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
		// ִ�кϳ����ί��
		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);
		return;
	}

	// �����Ʒ��ͬ���ҿ��Ժϲ�,����ȥһ��
	if (InputID == ObjectIndex && MultiplyAble(InputID)) {
		OutputID = ObjectIndex;
		// Ԥ�����������
		int PreOutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
		// ʵ�����������
		OutputNum = (PreOutputNum + InputNum <= 64) ? (PreOutputNum + InputNum) : 64;
		// ���±�������
		ObjectNum = ObjectNum - (OutputNum - InputNum);
		// ִ�кϳ����ί��
		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);
		return;
	}

	// �����Ʒ����ͬ������ͬ���ǲ��ܺϲ�,��������Ʒ����,���������Ʒ��һ��
	OutputID = ObjectIndex;
	// ������˫��
	OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
	// ִ�кϳ����ί��
	CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);
	// ִ�ж�����Ʒί��
	ThrowObject.ExecuteIfBound(InputID, InputNum);
}
