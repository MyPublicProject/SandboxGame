// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiPackageWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SiAiGameWidgetStyle.h"
#include "SOverlay.h"
#include "SBox.h"
#include "SImage.h"
#include "SUniformGridPanel.h"
#include "SBorder.h"
#include "SSiAiContainerBaseWidget.h"
#include "AiSiTypes.h"
#include "SiAiPackageManager.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "DrawElements.h"
#include "SlAiDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiPackageWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiGameStyle>("BPSiAiGameStyle");

	// 获取DPIScaler
	UIScaler = InArgs._UIScaler;

	ChildSlot
	[
		SNew(SOverlay)

		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(FMargin(0.f, 0.f, 50.f, 0.f))
		[
			SNew(SBox)
			.WidthOverride(800.f)
			.HeightOverride(800.f)
			[
				SNew(SOverlay)

				//背景图
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->PackageBGBrush)
				]

				//底部快捷栏
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.f, 680.f, 40.f, 40.f))
				[
					SAssignNew(ShortcutGrid, SUniformGridPanel)
				]

				//背包主体
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.f, 320.f, 40.f, 160.f))
				[
					SAssignNew(PackageGrid, SUniformGridPanel)
				]


				//合成表输入框
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(80.f, 40.f, 480.f, 520.f))
				[
					SAssignNew(CompoundGrid, SUniformGridPanel)
				]

				//合成表输出框
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(560.f, 120.f, 160.f, 600.f))
				[
					SAssignNew(OutputBorder, SBorder)
				]


				//合成小箭头
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(400.f, 120.f, 320.f, 600.f))
				[
					SNew(SImage)
					.Image(&GameStyle->CompoundArrowBrush)
				]
			]
		]
	];

	MousePosition = FVector2D(0.f, 0.f);

	IsInitPackageMana = false;
}

void SSiAiPackageWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (GetVisibility() == EVisibility::Visible && GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetMousePosition(MousePosition);

		MousePosition = MousePosition / UIScaler.Get();
	}
	// 如果背包管理器已经初始化
	if (IsInitPackageMana)
	{
		// 事实更新容器悬停显示
		SiAiPackageManager::Get()->UpdateHovered(MousePosition, AllottedGeometry);
	}
}

int32 SSiAiPackageWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// 先调用一下父类
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// 如果背包管理器还没有初始化
	if (!IsInitPackageMana) return LayerId;

	// 如果背包管理器的手上物品不为0， 就进行渲染
	if (GetVisibility() == EVisibility::Visible && SiAiPackageManager::Get()->ObjectIndex != 0 &&SiAiPackageManager::Get()->ObjectNum != 0)
	{
		// 渲染物品图标
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId + 30,
			AllottedGeometry.ToPaintGeometry(MousePosition - FVector2D(32.f, 32.f), FVector2D(64.f, 64.f)),
			SlAiDataHandle::Get()->ObjectBrushList[SiAiPackageManager::Get()->ObjectIndex],
			ESlateDrawEffect::None,
			FLinearColor(1.f, 1.f, 1.f, 1.f)
		);

		// 获取物品属性
		TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(SiAiPackageManager::Get()->ObjectIndex);
		// 渲染数量，如果是不可以叠加物品不渲染
		if (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon)
		{
			//渲染数量文字
			FSlateDrawElement::MakeText(
				OutDrawElements,
				LayerId + 30,
				AllottedGeometry.ToPaintGeometry(MousePosition + FVector2D(12.f, 16.f), FVector2D(16.f, 16.f)),
				FString::FromInt(SiAiPackageManager::Get()->ObjectNum),
				GameStyle->Font_Outline_16,
				ESlateDrawEffect::None,
				GameStyle->FontColor_Black
			);
		}
	}
	return LayerId;
}

FReply SSiAiPackageWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	// 若果背包没有初始化返回
	if (!IsInitPackageMana) return FReply::Handled();

	// 背包左键事件
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SiAiPackageManager::Get()->LeftOption(MousePosition, MyGeometry);
	}
	// 背包右键事件
	if (MouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		SiAiPackageManager::Get()->RightOption(MousePosition, MyGeometry);
	}

	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiPackageWidget::InitPackageManager()
{
	// 初始化快捷栏
	for (int i = 0; i < 9; i++)
	{
		// 创建容器实例
		TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Shortcut, i);
		// 将容器添加到UI
		ShortcutGrid->AddSlot(i, 0)[NewContainer->AsShared()];
		//注册容器到背包管理器
		SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Shortcut);
	}

	// 初始化背包主体
	for (int i = 0; i < 36; ++i) {
		TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Normal, i);
		PackageGrid->AddSlot(i % 9, i / 9)[NewContainer->AsShared()];
		SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Normal);
	}

	// 初始化合成台
	for (int i = 0; i < 9; ++i) {
		TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Input, i);
		CompoundGrid->AddSlot(i % 3, i / 3)[NewContainer->AsShared()];
		SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Input);
	}

	// 初始化输出容器
	TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Output, 1);
	OutputBorder->SetContent(NewContainer->AsShared());
	SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Output);

	// 设置已经初始化背包管理器
	IsInitPackageMana = true;
}
