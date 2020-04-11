// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"
#include "AiSiTypes.h"

// 合成输入委托
DECLARE_DELEGATE(FCompoundInput)
// 合成提取委托,参数是物品序号, 物品数量
DECLARE_DELEGATE_TwoParams(FCompoundOutput, int, int)
// 丢弃物品委托,参数是物品序号, 物品数量
DECLARE_DELEGATE_TwoParams(FThrowObject, int, int)
// 背包快捷栏更新状态引起游戏变化委托, 参数分别是快捷栏序号, 更新得物品ID, 更新物品数量
DECLARE_DELEGATE_ThreeParams(FPackShortChange, int, int, int)

/**
 * 
 */
class SANDBOXGAME_API SSiAiContainerBaseWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiContainerBaseWidget)
	{}

	SLATE_ATTRIBUTE(int, WorkIndex)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// 获取实例
	static TSharedPtr<SSiAiContainerBaseWidget> CreateContainer(EContainerType::Type NeedType, int WorkID);

	// 更新鼠标移动到上面的状态
	void UpdateHovered(bool IsHovered);

	// 重置自身属性
	virtual void ResetContainerPara(int ObjectID, int Num);

	// 获取容器的物品ID
	int GetIndex() const;

	// 获取容器的物品数量
	int GetNum() const;

	// 左键点击操作
	virtual void LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum);

	// 右键点击操作
	virtual void RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum);

public:

	// 合成输入委托
	FCompoundInput CompoundInput;
	// 合成输出委托
	FCompoundOutput CompoundOutput;
	// 丢弃物品委托
	FThrowObject ThrowObject;
	// 快捷栏更新委托
	FPackShortChange PackShortChange;


protected:

	// 获取是否可以叠加
	bool MultiplyAble(int ObjectID);

protected:

	// 容器各个组件
	TSharedPtr<SBorder> ContainerBorder;
	TSharedPtr<SBorder> ObjectImage;
	TSharedPtr<STextBlock> ObjectNumText;

	// 获取 MenuStyle
	const struct FSiAiGameStyle *GameStyle;

	// 工作序号，用于标记在背包中的位置作用
	TAttribute<int> WorkIndex;

	// 是否在Hover状态
	bool IsHover;

	// 物品序号
	int ObjectIndex;

	// 物品数量
	int ObjectNum;

};
