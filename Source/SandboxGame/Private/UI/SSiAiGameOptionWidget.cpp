// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiGameOptionWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SiAiMenuWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "SBorder.h"
#include "SOverlay.h"
#include "SCheckBox.h"
#include "SBoxPanel.h"
#include "STextBlock.h"
#include "SlAiDataHandle.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiGameOptionWidget::Construct(const FArguments& InArgs)
{
	// 获取编辑器的 MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");


	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(300.f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(&MenuStyle->GameOptionBGBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(50.f)
			[
				SNew(SVerticalBox)
				// 第一行
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.f)
					[
						SAssignNew(ZhCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SSiAiGameOptionWidget::ZhCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SiAiMenu", "Chinese", "Chinese"))
						]
					]
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.f)
					[
						SAssignNew(EnCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SSiAiGameOptionWidget::EnCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SiAiMenu", "English", "English"))
						]
					]
				]
				// 第二行
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				// 第三行
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
			]
		]
	];
	StyleInitialize();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiGameOptionWidget::StyleInitialize()
{
	// 设置 ZhCheckBox 样式
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	// 设置 EnCheckBox 样式
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		break;
	case ECultureTeam::ZH:
		EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
		break;
	}

}

void SSiAiGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	// 设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	// 告诉数据控制类转换为中文
	SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
}

void SSiAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	// 设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	// 告诉数据控制类转换为中文
	SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
}
