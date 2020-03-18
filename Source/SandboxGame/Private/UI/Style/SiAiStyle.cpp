// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiStyle.h"
#include "SlateGameResources.h"
#include "SlateStyleRegistry.h"

TSharedPtr<class FSlateStyleSet> SiAiStyle::Create()
{
	// ��Ŀ¼�������Ӧ�� C++ ��
	TSharedPtr<FSlateStyleSet> StyleRef = FSlateGameResources::New(SiAiStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	StyleRef->Set("MenuItemFont", FSlateFontInfo("Rboto-Regular.ttf", 50));
	return StyleRef;
}

TSharedPtr<FSlateStyleSet> SiAiStyle::SiAiStyleInstance = NULL;

void SiAiStyle::Initialze()
{
	if (!SiAiStyleInstance.IsValid()) {
		SiAiStyleInstance = Create();
		// ע�����ϵͳ����
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
	// ȡ��ע��
	FSlateStyleRegistry::UnRegisterSlateStyle(*SiAiStyleInstance);
	// ȷ����Ψһ��
	ensure(SiAiStyleInstance.IsUnique());
	SiAiStyleInstance.Reset();
}

const ISlateStyle& SiAiStyle::Get()
{
	return *SiAiStyleInstance;
}
