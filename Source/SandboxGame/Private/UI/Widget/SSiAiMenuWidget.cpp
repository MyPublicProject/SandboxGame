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
#include "Kismet/GameplayStatics.h"
#include "SiAiMenuController.h"
#include "SiAiHelper.h"
#include "SlateApplication.h"
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

	// 播放背景音乐
	FSlateApplication::Get().PlaySound(MenuStyle->MenuBackgroundMusic);
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
	InitializedAnimation();
}

void SSiAiMenuWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	switch (AnimState)
	{
	case EMenuAnim::Stop:
		break;
	case EMenuAnim::Close:
		//如果正在播放
		if (MenuAnimation.IsPlaying()) {
			//实时修改Menu的大小
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, -1.f);
			//在关闭了40%的时候设置不显示组件
			if (MenuCurve.GetLerp() < 0.6f && IsMenuShow) ChooseWidget(EMenuType::None);
		}
		else {
			//关闭动画完了,设置状态为打开
			AnimState = EMenuAnim::Open;
			//开始播放打开动画
			MenuAnimation.Play(this->AsShared());
		}
		break;
	case EMenuAnim::Open:
		//如果正在播放
		if (MenuAnimation.IsPlaying())
		{
			//实时修改Menu大小
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, CurrentHeight);
			//打开60%之后显示组件
			if (MenuCurve.GetLerp() > 0.6f && !IsMenuShow) ChooseWidget(CurrentMenu);
		}
		//如果已经播放完毕
		if (MenuAnimation.IsAtEnd())
		{
			//修改状态为Stop
			AnimState = EMenuAnim::Stop;
			//解锁按钮
			ControlLocked = false;
		}
		break;
	default:
		break;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	// 如果锁住，直接 Return
	if (ControlLocked) return;
	// 点击锁住按钮
	ControlLocked = true;
	
	switch (ItemType)
	{
	case EMenuItem::None:
		break;
	case EMenuItem::StartGame:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::GameOption:
		PlayClose(EMenuType::GameOption);
		break;
	case EMenuItem::QuitGame:
		//退出游戏,播放声音并且延时调用退出函数
		SiAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->ExitGameSound, this, &SSiAiMenuWidget::QuitGame);
		break;
	case EMenuItem::NewGame:
		PlayClose(EMenuType::NewGame);
		break;
	case EMenuItem::LoadRecord:
		PlayClose(EMenuType::ChooseRecord);
		break;
	case EMenuItem::StartGameGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::GameOptionGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::NewGameGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::ChooseRecordGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::EnterGame:
		// 检测是否可以进入游戏
		if (NewGameWidget->AllowEnterGame())
		{
			SiAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SSiAiMenuWidget::EnterGame);
		}
		else
		{
			ControlLocked = false;
		}
		break;
	case EMenuItem::EnterRecord:
		// 告诉选择存档更新文档名
		ChooseRecordWidget->UpdataRecordName();
		SiAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SSiAiMenuWidget::EnterGame);
		break;
	default:
		break;
	}
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
}

void SSiAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	// 是否显示菜单
	IsMenuShow = WidgetType != EMenuType::None;
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
}

// 如果不修改,传入-1
void SSiAiMenuWidget::ResetWidgetSize(float NewWidget, float NewHeight)
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

void SSiAiMenuWidget::InitializedAnimation()
{
	// 延迟
	const float StartDelay = 0.3f;
	// 持续时间
	const float AnimDuration = 0.6f;

	MenuAnimation = FCurveSequence();
	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);

	// 初始设置 Menu 大小
	ResetWidgetSize(600.f, 510.f);
	// 初始显示主界面
	ChooseWidget(EMenuType::MainMenu);
	// 允许点击按钮
	ControlLocked = false;
	// 设置动画状态为停止
	AnimState = EMenuAnim::Stop;
	// 设置动画播放器跳到结尾
	MenuAnimation.JumpToEnd();
}

void SSiAiMenuWidget::PlayClose(EMenuType::Type NewMenu)
{
	// 设置新的界面
	CurrentMenu = NewMenu;
	// 设置新高度
	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;
	// 设置播放状态
	AnimState = EMenuAnim::Close;
	// 播放反向动画
	MenuAnimation.PlayReverse(this->AsShared());
	// 播放切换菜单音乐
	FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);
}

void SSiAiMenuWidget::QuitGame()
{
	// 控制台
	Cast<ASiAiMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
}
void SSiAiMenuWidget::EnterGame()
{
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("GameMap"));
}
