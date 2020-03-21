// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"


// ί��
DECLARE_DELEGATE_OneParam(FItemClicked, const EMenuItem::Type)

/**
 * 
 */
class SANDBOXGAME_API SSiAiMenuItemWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiMenuItemWidget)
	{}

	SLATE_ATTRIBUTE(FText, ItemText)

	SLATE_EVENT(FItemClicked, OnClicked)

	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// ��д��ť OnMouseButtonDown ����
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	// ��д��ť OnMouseButtonUp ����
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	// ��д��ť OnMouseLeave ����
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

private:

	// ��ȡ��ɫ
	FSlateColor GetTintColor() const;

private:

	// ��ȡ MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;

	// �����¼�ί��
	FItemClicked OnClicked;

	EMenuItem::Type ItemType;

	// ��ť�Ƿ��Ѿ�����
	bool IsMouseButtonDown;

};
