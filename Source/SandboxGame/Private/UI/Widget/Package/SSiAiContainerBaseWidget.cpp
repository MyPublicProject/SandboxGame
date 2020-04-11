// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiContainerBaseWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SiAiGameWidgetStyle.h"
#include "SSiAiContainerOutputWidget.h"
#include "SSiAiContainerInputWidget.h"
#include "SSiAiContainerNormalWidget.h"
#include "SSiAiContainerShortcutWidget.h"
#include "SlAiDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiContainerBaseWidget::Construct(const FArguments& InArgs)
{
	// ��ȡ GameStyle
	GameStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiGameStyle>("BPSiAiGameStyle");
	// ��ȡ������
	WorkIndex = InArgs._WorkIndex;

	ChildSlot
	[
		SAssignNew(ContainerBorder, SBorder)
		.BorderImage(&GameStyle->NormalContainerBrush)
		.Padding(FMargin(8.f))
		[
			SAssignNew(ObjectImage, SBorder)
			.BorderImage(&GameStyle->EmptyBrush)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f, 0.f, 4.f, 0.f))
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Font(GameStyle->Font_Outline_16)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
	IsHover = false;

	// ��ʼ��ʱ��Ʒ��������Ŷ�Ϊ0
	ObjectIndex = ObjectNum = 0;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SSiAiContainerBaseWidget> SSiAiContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int WorkID)
{
	TSharedPtr<SSiAiContainerBaseWidget> ResultContainer;
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer, SSiAiContainerOutputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Input:
		SAssignNew(ResultContainer, SSiAiContainerInputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Normal:
		SAssignNew(ResultContainer, SSiAiContainerNormalWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Shortcut:
		SAssignNew(ResultContainer, SSiAiContainerShortcutWidget).WorkIndex(WorkID);
		break;
	}
	return ResultContainer;
}

void SSiAiContainerBaseWidget::UpdateHovered(bool IsHovered)
{
	// �������ƶ�������
	if (IsHovered)
	{
		if (!IsHover) ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
	}
	else
	{
		if(IsHover) ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
	}
	//  ����״̬
	IsHover = IsHovered;
}

void SSiAiContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
{
	// ��������ID����ͬ��������ͼ
	if (ObjectIndex != ObjectID)
	{
		ObjectImage->SetBorderImage(SlAiDataHandle::Get()->ObjectBrushList[ObjectID]);
	}

	ObjectIndex = ObjectID;
	ObjectNum = Num;

	// �����Ʒ�� ID Ϊ 0
	if (ObjectIndex == 0)
	{
		ObjectNumText->SetText(FText::FromString(""));
	}
	else
	{
		// �ж���Ʒ�Ƿ���Ե���
		if (MultiplyAble(ObjectIndex))
		{
			// ��ʾ����
			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
		}
		else
		{
			// ���ɵ��ӵĻ�����ʾ����
			ObjectNumText->SetText(FText::FromString(""));
		}
	}
}

int SSiAiContainerBaseWidget::GetIndex() const
{
	return ObjectIndex;
}

int SSiAiContainerBaseWidget::GetNum() const
{
	return ObjectIndex;
}

void SSiAiContainerBaseWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	// ���������Ʒ�뱾����Ʒ��ͬ���ҿ��Ե���
	if (InputID == ObjectIndex && MultiplyAble(ObjectIndex))
	{
		// ���������жϷ���ID,���ص�����ʱ������ͼ��
		OutputID = (ObjectNum + InputNum <= 64) ? 0 : InputID;
		// ���С��64������0�������򷵻ز�ֵ�����ص�����ʱ����������
		OutputNum = (ObjectNum + InputNum <= 64) ? 0 : (ObjectNum + InputNum - 64);
		// ���ñ�������,����Ϊ64
		ObjectNum = (ObjectNum + InputNum <= 64) ? (ObjectNum + InputNum) : 64;
		// ��������
		ResetContainerPara(ObjectIndex, ObjectNum);
		return;
	}
	// ֱ�Ӹ�������,�������ݼ�������
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	// ��������
	ResetContainerPara(InputID, InputNum);
}

void SSiAiContainerBaseWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	// �������Ϊ�գ�ֱ�Ӱѱ��ص�һ�����ȥ��ʹ�ý�һ��
	// InputID Ϊ��˵��û�л�����Ʒ
	if (InputID == 0)
	{
		OutputID = ObjectIndex;
		// ���ֵ�˫��
		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
		// ��������
		ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);
		return;
	}

	if (ObjectIndex == 0 || (InputID == ObjectIndex && MultiplyAble(InputID)))
	{
		// ���ݱ��������Ƿ񳬳���Χ���������
		OutputNum = (ObjectNum + 1 <= 64) ? (InputNum - 1) : InputNum;
		// ���������Ƿ�Ϊ�㶨������� ID
		OutputID = (OutputNum == 0) ? 0 : InputID;
		// ��������
		ResetContainerPara(InputID, (ObjectNum + 1 <= 64) ? (ObjectNum + 1) : ObjectNum);
		return;
	}

	// �����Ʒ����ͬ������ͬ���ǲ��ܺϲ�,ֱ�ӽ���
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	// ��������
	ResetContainerPara(InputID, InputNum);
}

bool SSiAiContainerBaseWidget::MultiplyAble(int ObjectID)
{
	// ��ȡ��Ʒ����
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectID);
	// �����Ƿ���������ֵ���ߣ������͹����ǲ����Ե��ӵ�
	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
}
