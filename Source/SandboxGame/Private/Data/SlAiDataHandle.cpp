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
	// 赋值
	CurrentCulture = Culture;
	//更新存档数据
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
	//更新存档数据
	SiAiSingleton<SiAiJsonHandle>::Get()->UpdataRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	// MakeShareable 创建共享指针共享引用
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle);
	return DataRef;
}

SlAiDataHandle::SlAiDataHandle()
{
	// 初始化存档数据
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
	// 获取语言
	FString Culture;
	// 读取存档数据
	SiAiSingleton<SiAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));
}
