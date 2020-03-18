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


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiMenuWidget::Construct(const FArguments& InArgs)
{
	// »ñÈ¡±à¼­Æ÷µÄ MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");
	
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
					]
				]
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
