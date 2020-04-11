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
	//��ȡGameStyle
	GameStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiGameStyle>("BPSiAiGameStyle");

	// ��ȡDPIScaler
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

				//����ͼ
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->PackageBGBrush)
				]

				//�ײ������
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.f, 680.f, 40.f, 40.f))
				[
					SAssignNew(ShortcutGrid, SUniformGridPanel)
				]

				//��������
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.f, 320.f, 40.f, 160.f))
				[
					SAssignNew(PackageGrid, SUniformGridPanel)
				]


				//�ϳɱ������
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(80.f, 40.f, 480.f, 520.f))
				[
					SAssignNew(CompoundGrid, SUniformGridPanel)
				]

				//�ϳɱ������
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(560.f, 120.f, 160.f, 600.f))
				[
					SAssignNew(OutputBorder, SBorder)
				]


				//�ϳ�С��ͷ
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
	// ��������������Ѿ���ʼ��
	if (IsInitPackageMana)
	{
		// ��ʵ����������ͣ��ʾ
		SiAiPackageManager::Get()->UpdateHovered(MousePosition, AllottedGeometry);
	}
}

int32 SSiAiPackageWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// �ȵ���һ�¸���
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// ���������������û�г�ʼ��
	if (!IsInitPackageMana) return LayerId;

	// ���������������������Ʒ��Ϊ0�� �ͽ�����Ⱦ
	if (GetVisibility() == EVisibility::Visible && SiAiPackageManager::Get()->ObjectIndex != 0 &&SiAiPackageManager::Get()->ObjectNum != 0)
	{
		// ��Ⱦ��Ʒͼ��
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId + 30,
			AllottedGeometry.ToPaintGeometry(MousePosition - FVector2D(32.f, 32.f), FVector2D(64.f, 64.f)),
			SlAiDataHandle::Get()->ObjectBrushList[SiAiPackageManager::Get()->ObjectIndex],
			ESlateDrawEffect::None,
			FLinearColor(1.f, 1.f, 1.f, 1.f)
		);

		// ��ȡ��Ʒ����
		TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(SiAiPackageManager::Get()->ObjectIndex);
		// ��Ⱦ����������ǲ����Ե�����Ʒ����Ⱦ
		if (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon)
		{
			//��Ⱦ��������
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
	// ��������û�г�ʼ������
	if (!IsInitPackageMana) return FReply::Handled();

	// ��������¼�
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SiAiPackageManager::Get()->LeftOption(MousePosition, MyGeometry);
	}
	// �����Ҽ��¼�
	if (MouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		SiAiPackageManager::Get()->RightOption(MousePosition, MyGeometry);
	}

	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiPackageWidget::InitPackageManager()
{
	// ��ʼ�������
	for (int i = 0; i < 9; i++)
	{
		// ��������ʵ��
		TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Shortcut, i);
		// ��������ӵ�UI
		ShortcutGrid->AddSlot(i, 0)[NewContainer->AsShared()];
		//ע������������������
		SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Shortcut);
	}

	// ��ʼ����������
	for (int i = 0; i < 36; ++i) {
		TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Normal, i);
		PackageGrid->AddSlot(i % 9, i / 9)[NewContainer->AsShared()];
		SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Normal);
	}

	// ��ʼ���ϳ�̨
	for (int i = 0; i < 9; ++i) {
		TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Input, i);
		CompoundGrid->AddSlot(i % 3, i / 3)[NewContainer->AsShared()];
		SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Input);
	}

	// ��ʼ���������
	TSharedPtr<SSiAiContainerBaseWidget> NewContainer = SSiAiContainerBaseWidget::CreateContainer(EContainerType::Output, 1);
	OutputBorder->SetContent(NewContainer->AsShared());
	SiAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Output);

	// �����Ѿ���ʼ������������
	IsInitPackageMana = true;
}
