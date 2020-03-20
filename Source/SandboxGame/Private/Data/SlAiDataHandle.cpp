// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiDataHandle.h"

TSharedPtr<SlAiDataHandle> SlAiDataHandle::DataInstance = NULL;

void SlAiDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam Culture)
{
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ECultureTeam::ZH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
		break;
	default:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		Culture = ECultureTeam::EN;
		break;
	}
	// 赋值
	CurrentCulture = Culture;
}

TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	// MakeShareable 创建共享指针共享引用
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle);
	return DataRef;
}

SlAiDataHandle::SlAiDataHandle()
{
}