// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiShortcutWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SiAiGameWidgetStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "STextBlock.h"
#include "SBorder.h"
#include "SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiShortcutWidget::Construct(const FArguments& InArgs)
{
	// 获取 GameStyle
	GameStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiGameStyle>("BPSiAiGameStyle");
	
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(900.f)
		.HeightOverride(160.f)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(ShortcutInfoTextBlock, STextBlock)
				.Font(GameStyle->Font_Outline_40)
				.ColorAndOpacity(GameStyle->FontColor_White)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.f, 60.f, 0.f, 0.f))
			[
				SAssignNew(GridPanel, SUniformGridPanel)
			]
		]
	];
}

void SSiAiShortcutWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!IsInitializeContainer)
	{
		InitializeContainer();
		IsInitializeContainer = true;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiShortcutWidget::InitializeContainer()
{
	for (int i = 0; i < 9; i++) 
	{
		// 创建容器
		TSharedPtr<SBorder> ContainerBordet;
		TSharedPtr<SBorder> ObjectImage;
		TSharedPtr<STextBlock> ObjectNumText;

		SAssignNew(ContainerBordet, SBorder)
		.Padding(FMargin(10.f))
		.BorderImage(&GameStyle->NormalContainerBrush)
		[
			SAssignNew(ObjectImage, SBorder)
			.BorderImage(&GameStyle->EmptyBrush)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Font(GameStyle->Font_Outline_20)
				.ColorAndOpacity(GameStyle->FontColor_Black)
				.Text(FText::FromString("Test"))
			]
		];
		GridPanel->AddSlot(i, 0)
		[
			ContainerBordet->AsShared()
		];
	}
}
