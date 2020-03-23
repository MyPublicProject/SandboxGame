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
// #include "Internationalization.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiMenuWidget::Construct(const FArguments& InArgs)
{
	// ��ȡ�༭���� MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");

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
	RootSizeBox->SetWidthOverride(600.f);
	RootSizeBox->SetHeightOverride(510.f);

	ContentBox->AddSlot()
	[
		SNew(SSiAiChooseRecordWidget)
	];
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
