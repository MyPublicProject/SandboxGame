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
	// 获取 GameStyle
	GameStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiGameStyle>("BPSiAiGameStyle");
	// 获取工作号
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

	// 初始化时物品数量和序号都为0
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
	// 如果鼠标移动到上面
	if (IsHovered)
	{
		if (!IsHover) ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
	}
	else
	{
		if(IsHover) ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
	}
	//  更新状态
	IsHover = IsHovered;
}

void SSiAiContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
{
	// 如果输入的ID不相同，更新贴图
	if (ObjectIndex != ObjectID)
	{
		ObjectImage->SetBorderImage(SlAiDataHandle::Get()->ObjectBrushList[ObjectID]);
	}

	ObjectIndex = ObjectID;
	ObjectNum = Num;

	// 如果物品的 ID 为 0
	if (ObjectIndex == 0)
	{
		ObjectNumText->SetText(FText::FromString(""));
	}
	else
	{
		// 判断物品是否可以叠加
		if (MultiplyAble(ObjectIndex))
		{
			// 显示数量
			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
		}
		else
		{
			// 不可叠加的话不显示数量
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
	// 如果输入物品与本地物品相同并且可以叠加
	if (InputID == ObjectIndex && MultiplyAble(ObjectIndex))
	{
		// 根据数量判断返回ID,返回等于零时不绘制图像
		OutputID = (ObjectNum + InputNum <= 64) ? 0 : InputID;
		// 如果小于64，返回0，大于则返回差值，返回等于零时不绘制文字
		OutputNum = (ObjectNum + InputNum <= 64) ? 0 : (ObjectNum + InputNum - 64);
		// 设置本地数量,上限为64
		ObjectNum = (ObjectNum + InputNum <= 64) ? (ObjectNum + InputNum) : 64;
		// 更新属性
		ResetContainerPara(ObjectIndex, ObjectNum);
		return;
	}
	// 直接更换数据,更换数据继续绘制
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	// 更新属性
	ResetContainerPara(InputID, InputNum);
}

void SSiAiContainerBaseWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	// 如果输入为空，直接把本地的一半给出去，使用进一发
	// InputID 为零说明没有绘制物品
	if (InputID == 0)
	{
		OutputID = ObjectIndex;
		// 区分单双数
		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
		// 更新属性
		ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);
		return;
	}

	if (ObjectIndex == 0 || (InputID == ObjectIndex && MultiplyAble(InputID)))
	{
		// 根据本地数量是否超出范围绑定输出数量
		OutputNum = (ObjectNum + 1 <= 64) ? (InputNum - 1) : InputNum;
		// 根据数量是否为零定义输出的 ID
		OutputID = (OutputNum == 0) ? 0 : InputID;
		// 更新属性
		ResetContainerPara(InputID, (ObjectNum + 1 <= 64) ? (ObjectNum + 1) : ObjectNum);
		return;
	}

	// 如果物品不相同或者相同但是不能合并,直接交换
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	// 更新属性
	ResetContainerPara(InputID, InputNum);
}

bool SSiAiContainerBaseWidget::MultiplyAble(int ObjectID)
{
	// 获取物品属性
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectID);
	// 返回是否是武器货值工具，武器和工具是不可以叠加的
	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
}
