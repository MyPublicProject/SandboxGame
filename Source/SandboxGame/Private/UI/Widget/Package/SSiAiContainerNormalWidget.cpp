// Fill out your copyright notice in the Description page of Project Settings.

#include "SSiAiContainerNormalWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSiAiContainerNormalWidget::Construct(const FArguments& InArgs)
{
	SSiAiContainerBaseWidget::Construct(
		SSiAiContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
