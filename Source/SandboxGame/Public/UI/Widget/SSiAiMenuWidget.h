// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"
#include "CurveSequence.h"
#include "CurveHandle.h"

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

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

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
	//初始化动画组件
	void InitializedAnimation();
	//播放关闭动画
	void PlayClose(EMenuType::Type NewMenu);
	//退出游戏
	void QuitGame();
	//进入游戏
	void EnterGame();

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

	// 动画播放器
	FCurveSequence MenuAnimation;
	// 曲线控制器
	FCurveHandle MenuCurve;
	// 用来保存新高度
	float CurrentHeight;
	// 是否已经显示 Menu 组件
	bool IsMenuShow;
	//是否锁住按钮
	bool ControlLocked;
	// 保存当前的动画状态
	EMenuAnim::Type AnimState;
	// 保存当前菜单
	EMenuType::Type CurrentMenu;
};
