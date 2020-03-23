// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"


// �޸���Ӣ��ί��
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)
// �޸�����ί��
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

class SSlider;
/**
 * 
 */
class SANDBOXGAME_API SSiAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiGameOptionWidget)
	{}
	SLATE_EVENT(FChangeCulture, ChangeCulture)
	SLATE_EVENT(FChangeVolume, ChangeVolume)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	// ͳһ������ʽ
	void StyleInitialize();
	// ���� CheckBox �¼�
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	// Ӣ�� CheckBox �¼�
	void EnCheckBoxStateChanged(ECheckBoxState NewState);
	// �����仯�¼�
	void MusicSliderChanged(float Value);
	// ��Ч�仯�¼�
	void SoundSliderChanged(float Value);

private:

	// ��ȡ MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;

	// ��ȡ CheckBox ָ��
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;
	
	// ����������
	TSharedPtr<SSlider> MuSlider;
	TSharedPtr<SSlider> SoSlider;
	// �������ٷֱ�
	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;

	// ί�б���
	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;
};