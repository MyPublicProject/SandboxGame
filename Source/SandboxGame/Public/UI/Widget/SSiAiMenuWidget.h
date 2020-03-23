// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"

class SBox;
class STextBlock;
class SVerticalBox;
struct MenuGroup;
class SSiAiGameOptionWidget;// ���ý���
class SSiAiNewGameWidget;// ����Ϸ����
class SSiAiChooseRecordWidget;// ��ȡ�浵����
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
	// ��ʼ�����пؼ�
	void InitializedMenuList();
	// ѡ����ʾ����
	void ChooseWidget(EMenuType::Type WidgetType);
	// �޸Ĳ˵���С
	void ResetWidgetSize(float NewWidget, float NewHeight);

private:
	// ������ڵ�
	TSharedPtr<SBox> RootSizeBox;
	// ��ȡ MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;
	// �������
	TSharedPtr<STextBlock> TitleText;
	// �������洹ֱ�б�
	TSharedPtr<SVerticalBox> ContentBox;
	// ����˵���
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	// ��Ϸ���� Widget ��ָ��
	TSharedPtr<SSiAiGameOptionWidget> GameOptionWidget;
	// ����Ϸ�ؼ�ָ��
	TSharedPtr<SSiAiNewGameWidget> NewGameWidget;
	// ѡ��浵�ؼ�ָ��
	TSharedPtr<SSiAiChooseRecordWidget> ChooseRecordWidget;
};
