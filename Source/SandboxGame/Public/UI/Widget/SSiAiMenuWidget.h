// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"

class SBox;
class STextBlock;
class SVerticalBox;
/**
 * 
 */
class SANDBOXGAME_API SSiAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	// �󶨸��� MenuItem �ķ���
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	// �޸�����	
	void ChangeCulture(ECultureTeam Culture);
	// �޸�����
	void ChangeVolume(const float MusicVolume, const float SoundVolume);

private:
	// ������ڵ�
	TSharedPtr<SBox> RootSizeBox;
	// ��ȡ MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;
	// �������
	TSharedPtr<STextBlock> TitleText;
	// �������洹ֱ�б�
	TSharedPtr<SVerticalBox> ContentBox;
};
