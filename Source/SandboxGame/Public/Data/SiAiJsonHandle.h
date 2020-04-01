// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AiSiTypes.h"
#include "Json.h"

/**
 * 
 */
class SANDBOXGAME_API SiAiJsonHandle
{
public:

	SiAiJsonHandle();

	// �����浵
	void RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList);

	// �޸Ĵ浵
	void UpdataRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString> *RecordDataList);

	// ������Ʒ����
	void ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>> &ObjectAttrMap);

	// ������Դ���Ժ���
	void ResourceAttrJsonRead(TMap<int, TSharedPtr<ResourceAttribute>>& ResourceAttrMap);

private:

	// ��ȡ Json �ļ����ַ���
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

	// FJsonObject ת��Ϊ Json ��ʽ���ַ���
	bool GetFStringInJsonData(const TSharedPtr<FJsonObject> &JsonObj, FString& JsonStr);

	// �����ַ������ļ�
	bool WriteFileWithJsonData(const FString &JsonStr, const FString &RelaPath, const FString &FileName);

	// �� String ת���� ObjectType �ķ���
	EObjectType::Type StringToObjectType(const FString ArgStr);

	//����һ���� String ת���� ResourceType �ķ���
	EResourceType::Type StringToResourceType(const FString ArgStr);

private:

	// �浵�ļ���
	FString RecordDataFileName;

	// ��Ʒ�����ļ���
	FString ObjectAttrFileName;

	// ��Դ�����ļ���
	FString ResourceAttrFileName;

	// ���·��
	FString RelativePath;

};