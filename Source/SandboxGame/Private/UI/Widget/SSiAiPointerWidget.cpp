// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiPointerWidget.h"
#include "SlateOptMacros.h"
#include "SiAiStyle.h"
#include "SiAiGameWidgetStyle.h"
#include "SBox.h"
#include "SlateStructs.h"
#include "SImage.h"
#include "Materials/MaterialInstance.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiPointerWidget::Construct(const FArguments& InArgs)
{
	// 获取GameStyle
	GameStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiGameStyle>("BPSiAiGameStyle");
	// 初始化大小
	CurrentSize = 20.f;
	IsAimed = false;

	ChildSlot
	[
		SAssignNew(RootBox, SBox)
		.WidthOverride(TAttribute<FOptionalSize>(this, &SSiAiPointerWidget::GetBoxWidget))
		.HeightOverride(TAttribute<FOptionalSize>(this, &SSiAiPointerWidget::GetBoxHeight))
		[
			SNew(SImage)
			.Image(&GameStyle->PointerBrush)
		]
	];
	// 加载材质实例
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> StaticPointerMaterialInstance(TEXT("MaterialInstanceConstant'/Game/Material/PointerMatInst.PointerMatInst'"));
	// 转换为动态材质实例
	PointerMaterial = (UMaterialInstanceDynamic*)StaticPointerMaterialInstance.Object;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSiAiPointerWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	CurrentSize = IsAimed ? FMath::FInterpTo(CurrentSize, 130.f, InDeltaTime, 10.f) : FMath::FInterpTo(CurrentSize, 20.f, InDeltaTime, 10.f);
}

void SSiAiPointerWidget::UpdatePointer(bool IsAim, float Range)
{
	IsAimed = IsAim;
	PointerMaterial->SetScalarParameterValue(FName("Range"), Range);
}

FOptionalSize SSiAiPointerWidget::GetBoxWidget() const
{
	return FOptionalSize(CurrentSize);
}

FOptionalSize SSiAiPointerWidget::GetBoxHeight() const
{
	return FOptionalSize(CurrentSize);
}
