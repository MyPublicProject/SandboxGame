// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"
#include "SlateStructs.h"

/**
 * 
 */
class SANDBOXGAME_API SSiAiPointerWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiPointerWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	// �� PlayerController �İ��¼�,�޸�׼���Ƿ������Լ����ؽ���
	void UpdatePointer(bool IsAim, float Range);

private:

	//��SBox��С�仯�󶨵ĺ���
	FOptionalSize GetBoxWidget() const;
	FOptionalSize GetBoxHeight() const;

private:

	// ��ȡGameStyle
	const struct FSiAiGameStyle *GameStyle;

	TSharedPtr<class SBox> RootBox;

	// ʵʱ�ı�Ĵ�С,�ı���������Ϳ��Ըı�׼�Ǵ�С
	float CurrentSize;

	// ��ȡ����ʵ��
	class UMaterialInstanceDynamic* PointerMaterial;

	// �Ƿ�ı��С״̬
	bool IsAimed;

};
