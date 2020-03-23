// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiChooseRecordWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SiAiMenuWidgetStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SImage.h"
#include "STextBlock.h"
#include "STextComboBox.h"
#include "SlAiDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiChooseRecordWidget::Construct(const FArguments& InArgs)
{
	// 获取MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");

	// 初始化下拉菜单
	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; It++) {
		OptionsSource.Add(MakeShareable(new FString(*It)));
	}

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(20.f, 0.f, 0.f, 0.f))
			[
				SNew(STextBlock)
				.Font(MenuStyle->Font_40)
				.Text(NSLOCTEXT("SiAiMenu", "NewGame", "NewGame"))
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 0.f, 20.f, 0.f))
			[
				SNew(SBox)
				.WidthOverride(300.f)
				.HeightOverride(60.f)
				[
					SAssignNew(RecordComboBox, STextComboBox)
					.Font(MenuStyle->Font_30)
					.OptionsSource(&OptionsSource)
				]
			]
		]
	];

	// 设置默认项
	RecordComboBox->SetSelectedItem(OptionsSource[0]);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiChooseRecordWidget::UpdataRecordName()
{
	//修改存档名
	SlAiDataHandle::Get()->RecordName = *RecordComboBox->GetSelectedItem().Get();
}
