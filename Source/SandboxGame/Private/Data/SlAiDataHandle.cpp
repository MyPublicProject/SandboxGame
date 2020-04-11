// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiDataHandle.h"
#include "SiAiJsonHandle.h"
#include "SiAiSingleton.h"
#include "SiAiHelper.h"
#include "Class.h"
#include "SiAiStyle.h"
#include "SiAiMenuWidgetStyle.h"
#include "Sound/SoundCue.h"
#include "SiAiGameWidgetStyle.h"

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
	// ���´浵����
	SiAiSingleton<SiAiJsonHandle>::Get()->UpdataRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol >= 0)
	{
		MusicVolume = MusicVol;
		// ѭ�����ñ�������
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator()); It; It++)
		{
			// ��������
			(*It)->VolumeMultiplier = MusicVolume;
		}
	}
	if (SoundVol >= 0)
	{
		SoundVolume = SoundVol;
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator()); It; It++)
		{
			// ��������
			(*It)->VolumeMultiplier = SoundVolume;
		}
	}
	//���´浵����
	SiAiSingleton<SiAiJsonHandle>::Get()->UpdataRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::InitializeGameData()
{
	// ��ʼ����Ʒ����
	InitObjectAtte();
	// ��ʼ����Դ����ͼ
	InitResourceAttrMap();

	bIsGameData = true;
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
	// ��ʼ�� Menu Sound ����
	InitializedMenuAudio();

	bIsGameData = false;
}

template<typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return FString("InValid");
	}
	return EnumPtr->GetNameStringByIndex((int32)Value);
}

template<typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}

void SlAiDataHandle::InitRecordData()
{
	// �浵����ʼ��
	RecordName = FString("");
	// ��ȡ����
	FString Culture;
	// ��ȡ�浵����
	SiAiSingleton<SiAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));
}

void SlAiDataHandle::InitializedMenuAudio()
{
	// ��ȡ MenuStyle
	MenuStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiMenuStyle>("BPSiAiMenuStyle");

	// �����Դ�ļ�����Դ�б�
	TArray<USoundCue*> MusicList;
	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));

	TArray<USoundCue*> SoundList;
	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));

	//�����Դ��Map
	MenuAudioResource.Add(FString("Music"), MusicList);
	MenuAudioResource.Add(FString("Sound"), SoundList);

	//����һ������
	ResetMenuVolume(MusicVolume, SoundVolume);
}

void SlAiDataHandle::InitObjectAtte()
{
	SiAiSingleton<SiAiJsonHandle>::Get()->ObjectAttrJsonRead(ObjectAttrMap);

	// ��ȡGameStyle
	GameStyle = &SiAiStyle::Get().GetWidgetStyle<FSiAiGameStyle>("BPSiAiGameStyle");

	// ����ˢ����
	ObjectBrushList.Add(&GameStyle->EmptyBrush);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_1);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_2);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_3);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_4);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_5);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_6);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_7);
}

void SlAiDataHandle::InitResourceAttrMap()
{
	SiAiSingleton<SiAiJsonHandle>::Get()->ResourceAttrJsonRead(ResourceAttrMap);
}
