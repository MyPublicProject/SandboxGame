// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"

class SBox;
class STextBlock;
class SVerticalBox;
struct MenuGroup;
class SSiAiGameOptionWidget;// 设置界面
class SSiAiNewGameWidget;// 新游戏界面
class SSiAiChooseRecordWidget;// 读取存档界面
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

	// 绑定各个 MenuItem 的方法
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	// 修改语言	
	void ChangeCulture(ECultureTeam Culture);
	// 修改音量
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	// 初始化所有控件
	void InitializedMenuList();
	// 选择显示界面
	void ChooseWidget(EMenuType::Type WidgetType);
	// 修改菜单大小
	void ResetWidgetSize(float NewWidget, float NewHeight);

private:
	// 保存根节点
	TSharedPtr<SBox> RootSizeBox;
	// 获取 MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;
	// 保存标题
	TSharedPtr<STextBlock> TitleText;
	// 用来保存垂直列表
	TSharedPtr<SVerticalBox> ContentBox;
	// 保存菜单组
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	// 游戏设置 Widget 的指针
	TSharedPtr<SSiAiGameOptionWidget> GameOptionWidget;
	// 新游戏控件指针
	TSharedPtr<SSiAiNewGameWidget> NewGameWidget;
	// 选择存档控件指针
	TSharedPtr<SSiAiChooseRecordWidget> ChooseRecordWidget;
};
