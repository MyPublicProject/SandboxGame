// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiDataHandle.h"
#include "SiAiJsonHandle.h"
#include "SiAiSingleton.h"
#include "SiAiHelper.h"
#include "Class.h"

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
	//���´浵����
	SiAiSingleton<SiAiJsonHandle>::Get()->UpdataRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
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
	//���´浵����
	SiAiSingleton<SiAiJsonHandle>::Get()->UpdataRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	// MakeShareable ��������ָ�빲������
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle);
	return DataRef;
}

SlAiDataHandle::SlAiDataHandle()
{
	// ��ʼ���浵����
	InitRecordData();
}

template<typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return FString("InValid");
	}
	return EnumPtr->GetNameStringByIndex((int32)Value);
}

template<typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}

void SlAiDataHandle::InitRecordData()
{
	// ��ȡ����
	FString Culture;
	// ��ȡ�浵����
	SiAiSingleton<SiAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));
}
