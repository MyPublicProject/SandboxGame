// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"
#include "AiSiTypes.h"

// �ϳ�����ί��
DECLARE_DELEGATE(FCompoundInput)
// �ϳ���ȡί��,��������Ʒ���, ��Ʒ����
DECLARE_DELEGATE_TwoParams(FCompoundOutput, int, int)
// ������Ʒί��,��������Ʒ���, ��Ʒ����
DECLARE_DELEGATE_TwoParams(FThrowObject, int, int)
// �������������״̬������Ϸ�仯ί��, �����ֱ��ǿ�������, ���µ���ƷID, ������Ʒ����
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

	// ��ȡʵ��
	static TSharedPtr<SSiAiContainerBaseWidget> CreateContainer(EContainerType::Type NeedType, int WorkID);

	// ��������ƶ��������״̬
	void UpdateHovered(bool IsHovered);

	// ������������
	virtual void ResetContainerPara(int ObjectID, int Num);

	// ��ȡ��������ƷID
	int GetIndex() const;

	// ��ȡ��������Ʒ����
	int GetNum() const;

	// ����������
	virtual void LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum);

	// �Ҽ��������
	virtual void RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum);

public:

	// �ϳ�����ί��
	FCompoundInput CompoundInput;
	// �ϳ����ί��
	FCompoundOutput CompoundOutput;
	// ������Ʒί��
	FThrowObject ThrowObject;
	// ���������ί��
	FPackShortChange PackShortChange;


protected:

	// ��ȡ�Ƿ���Ե���
	bool MultiplyAble(int ObjectID);

protected:

	// �����������
	TSharedPtr<SBorder> ContainerBorder;
	TSharedPtr<SBorder> ObjectImage;
	TSharedPtr<STextBlock> ObjectNumText;

	// ��ȡ MenuStyle
	const struct FSiAiGameStyle *GameStyle;

	// ������ţ����ڱ���ڱ����е�λ������
	TAttribute<int> WorkIndex;

	// �Ƿ���Hover״̬
	bool IsHover;

	// ��Ʒ���
	int ObjectIndex;

	// ��Ʒ����
	int ObjectNum;

};
