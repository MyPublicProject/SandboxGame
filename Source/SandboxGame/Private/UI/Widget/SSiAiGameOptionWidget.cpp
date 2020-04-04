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
#include "SSlider.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiGameOptionWidget::Construct(const FArguments& InArgs)
{
	// 获取编辑器的 MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");

	// 获取委托
	ChangeCulture = InArgs._ChangeCulture;
	ChangeVolume = InArgs._ChangeVolume;

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
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SiAiMenu", "Music", "Music"))
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.f)
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Fill)
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBarBrush)
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								SAssignNew(MuSlider, SSlider)
								.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this, &SSiAiGameOptionWidget::MusicSliderChanged)
							]
						]
					]
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(MuTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
				// 第三行
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.f)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SiAiMenu", "Sound", "Sound"))
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.f)
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Fill)
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBarBrush)
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								SAssignNew(SoSlider, SSlider)
								.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this, &SSiAiGameOptionWidget::SoundSliderChanged)
							]
						]
					]
					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(SoTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
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

	// 默认滑动条
	MuSlider->SetValue(SlAiDataHandle::Get()->MusicVolume);
	SoSlider->SetValue(SlAiDataHandle::Get()->SoundVolume);
	// 百分比 // 我觉得不需要这两行代码
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->MusicVolume * 100)) + FString("%")));
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->SoundVolume * 100)) + FString("%")));
}

void SSiAiGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	// 设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	// 告诉数据控制类转换为中文
	// SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
	ChangeCulture.ExecuteIfBound(ECultureTeam::ZH);
}

void SSiAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	// 设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	// 告诉数据控制类转换为中文
	// SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);
}

void SSiAiGameOptionWidget::MusicSliderChanged(float Value)
{
	// 显示百分比
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	// 修改音量
	// SlAiDataHandle::Get()->ResetMenuVolume(Value, -1.f);
	ChangeVolume.ExecuteIfBound(Value, -1.f);
}

void SSiAiGameOptionWidget::SoundSliderChanged(float Value)
{
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	// SlAiDataHandle::Get()->ResetMenuVolume(-1.f, Value);
	ChangeVolume.ExecuteIfBound(-1.f, Value);
}