// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AiSiTypes.h"

class USoundCue;

/**
 * 
 */
class SANDBOXGAME_API SlAiDataHandle
{
public:
	
	SlAiDataHandle();
	
	static void Initialize();

	static TSharedPtr<SlAiDataHandle> Get();

	// �޸���Ӣ��
	void ChangeLocalizationCulture(ECultureTeam Culture);

	// �޸Ĳ˵�����
	void ResetMenuVolume(float MusicVal, float SoundVal);
	
	// ��Ϸ���ݳ�ʼ��
	void InitializeGameData();

public:

	// ����
	ECultureTeam CurrentCulture;

	// ����
	float MusicVolume;
	float SoundVolume;

	// �浵����
	TArray<FString> RecordDataList;

	// �浵��
	FString RecordName;

	// ��Ʒ����
	TMap<int, TSharedPtr<ObjectAttribute>> ObjectAttrMap;

	// ��Ʒ��ͼ��Դ����
	TArray<const FSlateBrush*> ObjectBrushList;

	// ��Դ����ͼ
	TMap<int, TSharedPtr<ResourceAttribute>> ResourceAttrMap;

	// GameModeData �Ƿ��ʼ��
	bool bIsGameData;

private:

	// ��������
	static TSharedRef<SlAiDataHandle> Create();

	// ���� enum ���ͻ�ȡ�ַ���
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	// �����ַ�����ȡ Enum ֵ
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);

	// ��ʼ���浵����
	void InitRecordData();

	// ��ʼ�� Menu ��������
	void InitializedMenuAudio();

	// ��ʼ����Ʒ����
	void InitObjectAtte();

	// ��ʼ����Դ����ͼ
	void InitResourceAttrMap();

private:

	static TSharedPtr<SlAiDataHandle> DataInstance;

	// ���� Menu ������
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;

	//��ȡMenuStyle,�������������ļ�
	const struct FSiAiMenuStyle *MenuStyle;

	//��ȡGameStyle
	const struct FSiAiGameStyle* GameStyle;

};
