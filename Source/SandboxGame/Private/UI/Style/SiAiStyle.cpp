// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiStyle.h"
#include "SlateGameResources.h"
#include "SlateStyleRegistry.h"

TSharedPtr<class FSlateStyleSet> SiAiStyle::Create()
{
	// 在目录下找相对应的 C++ 类
	TSharedPtr<FSlateStyleSet> StyleRef = FSlateGameResources::New(SiAiStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	StyleRef->Set("MenuItemFont", FSlateFontInfo("Rboto-Regular.ttf", 50));
	return StyleRef;
}

TSharedPtr<FSlateStyleSet> SiAiStyle::SiAiStyleInstance = NULL;

void SiAiStyle::Initialze()
{
	if (!SiAiStyleInstance.IsValid()) {
		SiAiStyleInstance = Create();
		// 注册进入系统里面
		FSlateStyleRegistry::RegisterSlateStyle(*SiAiStyleInstance);
	}
}

FName SiAiStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SiAiStyle"));
	return StyleSetName;
}

void SiAiStyle::ShutDown()
{
	// 取消注册
	FSlateStyleRegistry::UnRegisterSlateStyle(*SiAiStyleInstance);
	// 确保是唯一的
	ensure(SiAiStyleInstance.IsUnique());
	SiAiStyleInstance.Reset();
}

const ISlateStyle& SiAiStyle::Get()
{
	return *SiAiStyleInstance;
}
