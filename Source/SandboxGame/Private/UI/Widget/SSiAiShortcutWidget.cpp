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
#include "AiSiTypes.h"
#include "SlAiDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiShortcutWidget::Construct(const FArguments& InArgs)
{
	// ��ȡ GameStyle
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

	//����û�г�ʼ������
	IsInitializeContainer = false;
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
	TArray<TSharedPtr<ShortcutContainer>> ContainerList;

	for (int i = 0; i < 9; i++) 
	{
		// ��������
		TSharedPtr<SBorder> ContainerBorder;
		TSharedPtr<SBorder> ObjectImage;
		TSharedPtr<STextBlock> ObjectNumText;

		SAssignNew(ContainerBorder, SBorder)
		.Padding(FMargin(10.f))
		[
			SAssignNew(ObjectImage, SBorder)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f, 0.f, 5.f, 0.f))
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Font(GameStyle->Font_Outline_20)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		];
		// ��������ӵ�����
		GridPanel->AddSlot(i, 0)
		[
			ContainerBorder->AsShared()
		];
		// ʵ����һ�������ṹ��
		TSharedPtr<ShortcutContainer> Container = MakeShareable(new ShortcutContainer(ContainerBorder, ObjectImage, ObjectNumText, &GameStyle->NormalContainerBrush, &GameStyle->ChoosedContainerBrush, SlAiDataHandle::Get()->ObjectBrushList));
		// ����ǵ�һ����������Ϊѡ��״̬
		if (i == 0) Container->SetChoosed(true);
		
		ContainerList.Add(Container);
	}
	// ��ʵ�����Ľṹ��ע��� PlayerState ������������
	RegisterShortcutContainer.ExecuteIfBound(&ContainerList, ShortcutInfoTextBlock);
}
