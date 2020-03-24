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
	// �˵�����
	FText MenuName;
	// �˵��߶�
	float MenuHeight;
	// �˵����
	float MenuWidth;
	// �������
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;
	// ���캯��
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
	// ��ȡ�༭���� MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");

	// ���ű�������
	FSlateApplication::Get().PlaySound(MenuStyle->MenuBackgroundMusic);
	// ��������
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
		//������ڲ���
		if (MenuAnimation.IsPlaying()) {
			//ʵʱ�޸�Menu�Ĵ�С
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, -1.f);
			//�ڹر���40%��ʱ�����ò���ʾ���
			if (MenuCurve.GetLerp() < 0.6f && IsMenuShow) ChooseWidget(EMenuType::None);
		}
		else {
			//�رն�������,����״̬Ϊ��
			AnimState = EMenuAnim::Open;
			//��ʼ���Ŵ򿪶���
			MenuAnimation.Play(this->AsShared());
		}
		break;
	case EMenuAnim::Open:
		//������ڲ���
		if (MenuAnimation.IsPlaying())
		{
			//ʵʱ�޸�Menu��С
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, CurrentHeight);
			//��60%֮����ʾ���
			if (MenuCurve.GetLerp() > 0.6f && !IsMenuShow) ChooseWidget(CurrentMenu);
		}
		//����Ѿ��������
		if (MenuAnimation.IsAtEnd())
		{
			//�޸�״̬ΪStop
			AnimState = EMenuAnim::Stop;
			//������ť
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
	// �����ס��ֱ�� Return
	if (ControlLocked) return;
	// �����ס��ť
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
		//�˳���Ϸ,��������������ʱ�����˳�����
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
		// ����Ƿ���Խ�����Ϸ
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
		// ����ѡ��浵�����ĵ���
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
	// ʵ����������
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
	// SSiAiMenuItemWidget ��ť����
	MainMenuList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "StartGame", "StartGame")).ItemType(EMenuItem::StartGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GameOption", "GameOption")).ItemType(EMenuItem::GameOption).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "QuitGame", "QuitGame")).ItemType(EMenuItem::QuitGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "Menu", "Menu"), 510.f, 600.f, &MainMenuList)));

	// ��ʼ��Ϸ����
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "NewGame", "NewGame")).ItemType(EMenuItem::NewGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "LoadRecord", "LoadRecord")).ItemType(EMenuItem::LoadRecord).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::StartGameGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "StartGame", "StartGame"), 510.f, 600.f, &StartGameList)));

	// ��Ϸ���ý���
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
	// ʵ������Ϸ���õ� Widget
	SAssignNew(GameOptionWidget, SSiAiGameOptionWidget)
		.ChangeCulture(this, &SSiAiMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SSiAiMenuWidget::ChangeVolume);
	// ��ӿؼ�������
	GameOptionList.Add(GameOptionWidget);
	GameOptionList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::GameOptionGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "GameOption", "GameOption"), 610.f, 600.f, &GameOptionList)));

	// ��ʼ����Ϸ����
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget, SSiAiNewGameWidget);
	NewGameList.Add(NewGameWidget);
	NewGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "EnterGame", "EnterGame")).ItemType(EMenuItem::EnterGame).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	NewGameList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::NewGameGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "NewGame", "NewGame"), 510.f, 600.f, &NewGameList)));

	//ѡ��浵����
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget, SSiAiChooseRecordWidget);
	ChooseRecordList.Add(ChooseRecordWidget);
	ChooseRecordList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "EnterRecord", "EnterRecord")).ItemType(EMenuItem::EnterRecord).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));
	ChooseRecordList.Add(SNew(SSiAiMenuItemWidget).ItemText(NSLOCTEXT("SiAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::ChooseRecordGoBack).OnClicked(this, &SSiAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("SiAiMenu", "LoadRecord", "LoadRecord"), 510.f, 600.f, &ChooseRecordList)));
}

void SSiAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	// �Ƿ���ʾ�˵�
	IsMenuShow = WidgetType != EMenuType::None;
	// �Ƴ��������
	ContentBox->ClearChildren();
	// ��� Menutype �� None
	if (WidgetType == EMenuType::None) return;
	// ѭ��������
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; It++)
	{
		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
	}
	// ���ı���
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);
}

// ������޸�,����-1
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
	// �ӳ�
	const float StartDelay = 0.3f;
	// ����ʱ��
	const float AnimDuration = 0.6f;

	MenuAnimation = FCurveSequence();
	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);

	// ��ʼ���� Menu ��С
	ResetWidgetSize(600.f, 510.f);
	// ��ʼ��ʾ������
	ChooseWidget(EMenuType::MainMenu);
	// ��������ť
	ControlLocked = false;
	// ���ö���״̬Ϊֹͣ
	AnimState = EMenuAnim::Stop;
	// ���ö���������������β
	MenuAnimation.JumpToEnd();
}

void SSiAiMenuWidget::PlayClose(EMenuType::Type NewMenu)
{
	// �����µĽ���
	CurrentMenu = NewMenu;
	// �����¸߶�
	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;
	// ���ò���״̬
	AnimState = EMenuAnim::Close;
	// ���ŷ��򶯻�
	MenuAnimation.PlayReverse(this->AsShared());
	// �����л��˵�����
	FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);
}

void SSiAiMenuWidget::QuitGame()
{
	// ����̨
	Cast<ASiAiMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
}
void SSiAiMenuWidget::EnterGame()
{
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("GameMap"));
}
