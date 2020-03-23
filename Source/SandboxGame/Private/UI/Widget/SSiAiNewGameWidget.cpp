// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiNewGameWidget.h"
#include "SlateOptMacros.h"
#include "SiAiMenuWidgetStyle.h"
#include "SiAiStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SImage.h"
#include "STextBlock.h"
#include "SEditableTextBox.h"
#include "SlAiDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiNewGameWidget::Construct(const FArguments& InArgs)
{
	//��ȡMenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");
	
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
					SAssignNew(EditTextBox, SEditableTextBox)
					.HintText(NSLOCTEXT("SiAiMenu", "RecordNameHint", "Input Record Name"))
					.Font(MenuStyle->Font_30)
				]
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

bool SSiAiNewGameWidget::AllowEnterGame()
{
	// ��ȡ������´浵��
	FText InputText = EditTextBox->GetText();
	// �Ƿ�Ϊ��
	if (InputText.ToString().IsEmpty()) return false;
	// ��ѯ�Ƿ���ڴ浵
	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; It++) {
		if ((*It).Equals(InputText.ToString()))
		{
			// ���� TextBox Ϊ��
			EditTextBox->SetText(FText::FromString(""));
			// ���� Hint δ�浵���ظ�
			EditTextBox->SetText(NSLOCTEXT("SiAiMenu", "NameRepeatedHint", "Record Name Repeated"));
			return false;
		}
	}
	// �����µĴ浵��
	SlAiDataHandle::Get()->RecordName = InputText.ToString();
	return true;
}
