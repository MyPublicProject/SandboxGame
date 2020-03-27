// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiGameWidgetStyle.h"


FSiAiGameStyle::FSiAiGameStyle()
{
}

FSiAiGameStyle::~FSiAiGameStyle()
{
}

const FName FSiAiGameStyle::TypeName(TEXT("FSiAiGameStyle"));

const FSiAiGameStyle& FSiAiGameStyle::GetDefault()
{
	static FSiAiGameStyle Default;
	return Default;
}

void FSiAiGameStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

