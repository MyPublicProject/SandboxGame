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
	// ��ֵ
	CurrentCulture = Culture;
}

void SlAiDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol >= 0)
	{
		MusicVolume = MusicVol;
	}
	if (SoundVol >= 0)
	{
		SoundVolume = SoundVol;
	}	
}

TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	// MakeShareable ��������ָ�빲������
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle);
	return DataRef;
}

SlAiDataHandle::SlAiDataHandle()
{
	// Ĭ��Ϊ������ʾ
	CurrentCulture = ECultureTeam::ZH;
	// ��ʼ������
	MusicVolume = 0.5f;
	SoundVolume = 0.5f;
}