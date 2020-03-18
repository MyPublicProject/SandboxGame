// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiMenuWidgetStyle.h"


FSiAiMenuStyle::FSiAiMenuStyle()
{
}

FSiAiMenuStyle::~FSiAiMenuStyle()
{
}

const FName FSiAiMenuStyle::TypeName(TEXT("FSiAiMenuStyle"));

const FSiAiMenuStyle& FSiAiMenuStyle::GetDefault()
{
	static FSiAiMenuStyle Default;
	return Default;
}

void FSiAiMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

