// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiMenuWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SiAiMenuWidgetStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SImage.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "SSiAiMenuItemWidget.h"
#include "SBoxPanel.h"
#include "AiSiTypes.h"
#include "Engine/Engine.h"
#include "SSiAiGameOptionWidget.h"
#include "SlAiDataHandle.h"
#include "SSiAiNewGameWidget.h"
#include "SSiAiChooseRecordWidget.h"
#include "SharedPointer.h"
// #include "Internationalization.h"

struct MenuGroup
{
	// 菜单标题
	FText MenuName;
	// 菜单高度
	float MenuHeight;
	// 菜单宽度
	float MenuWidth;
	// 下属组件
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;
	// 构造函数
	MenuGroup(const FText Name, const float Height, const float Wdith, TArray<TSharedPtr<SCompoundWidget>> *Children)
	{
		MenuName = Name;
		MenuHeight = Height;
		MenuWidth = Wdith;
		for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(*Children); It; It++)
		{
			ChildWidget.Add(*It);
		}
	}
};


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiMenuWidget::Construct(const FArguments& InArgs)
{
	// 获取编辑器的 MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");

	// 语言设置
	// FInternationalization::Get().SetCurrentCulture(TEXT("en"));
	// FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
	
	ChildSlot
	[
		SAssignNew(RootSizeBox, SBox)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.f, 50.f, 0.f, 0.f))
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuBackgroundBrush)
			]
			
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
			[
				SNew(SImage)
				.Image(&MenuStyle->LeftIconBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
			[
				SNew(SImage)
				.Image(&MenuStyle->RightIconBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBox)
				.WidthOverride(400.f)
				.HeightOverride(100.f)
				[
					SNew(SBorder)
					.BorderImage(&MenuStyle->TitleBorderBrush)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SAssignNew(TitleText, STextBlock)
						.Font(SiAiStyle::Get().GetFontStyle("MenuItemFont"))
						.Text(NSLOCTEXT("SiAiMenu", "Menu", "Menu"))
					]
				]
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.Padding(FMargin(0.f, 130.f, 0.f, 0.f))
			[
				SAssignNew(ContentBox, SVerticalBox)
			]
		]
	];
	InitializedMenuList();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	
}

void SSiAiMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	SlAiDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

void SSiAiMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	SlAiDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}

void SSiAiMenuWidget::InitializedMenuList()
{
	// 实例化主界面
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
	// SSiAiMenuItemWidget 按钮界面
	MainMenuList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "StartGame", "StartGame")).ItemType(EMenuItem::StartGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GameOption", "GameOption")).ItemType(EMenuItem::GameOption).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "QuitGame", "QuitGame")).ItemType(EMenuItem::QuitGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "Menu", "Menu"), 510.f, 600.f, &MainMenuList)));

	// 开始游戏界面
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "NewGame", "NewGame")).ItemType(EMenuItem::NewGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "LoadRecord", "LoadRecord")).ItemType(EMenuItem::LoadRecord).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::StartGameGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "StartGame", "StartGame"), 510.f, 600.f, &StartGameList)));

	// 游戏设置界面
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
	// 实例化游戏设置的 Widget
	SAssignNew(GameOptionWidget, SSiAiGameOptionWidget)
		.ChangeCulture(this, &SSiAiMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SSiAiMenuWidget::ChangeVolume);
	// 添加控件到数据
	GameOptionList.Add(GameOptionWidget);
	GameOptionList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::GameOptionGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "GameOption", "GameOption"), 610.f, 600.f, &GameOptionList)));

	// 开始新游戏界面
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget, SSiAiNewGameWidget);
	NewGameList.Add(NewGameWidget);
	NewGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "EnterGame", "EnterGame")).ItemType(EMenuItem::EnterGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	NewGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::NewGameGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "NewGame", "NewGame"), 510.f, 600.f, &NewGameList)));

	//选择存档界面
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget, SSiAiChooseRecordWidget);
	ChooseRecordList.Add(ChooseRecordWidget);
	ChooseRecordList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "EnterRecord", "EnterRecord")).ItemType(EMenuItem::EnterRecord).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	ChooseRecordList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::ChooseRecordGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "LoadRecord", "LoadRecord"), 510.f, 600.f, &ChooseRecordList)));


	ChooseWidget(EMenuType::MainMenu);
}

void SSiAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	// 是否显示菜单
	// IsMenuShow = WidgetType != EMenuType::None;
	// 移除所有组件
	ContentBox->ClearChildren();
	// 如果 Menutype 是 None
	if (WidgetType == EMenuType::None) return;
	// 循环添加组件
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; It++)
	{
		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
	}
	// 更改标题
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);
	// 修改 Menu Size
	ResetWidgetSize((*MenuMap.Find(WidgetType))->MenuHeight, (*MenuMap.Find(WidgetType))->MenuWidth);
}

// 如果不修改,传入-1
void SSiAiMenuWidget::ResetWidgetSize(float NewHeight, float NewWidget)
{
	if (NewWidget > 0)
	{
		RootSizeBox->SetWidthOverride(NewWidget);
	}
	
	if (NewHeight > 0)
	{
		RootSizeBox->SetHeightOverride(NewHeight);
	}
}
