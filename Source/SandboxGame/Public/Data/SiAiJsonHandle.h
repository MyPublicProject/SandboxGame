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

private:

	// ��ȡ Json �ļ����ַ���
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

private:

	// �浵�ļ���
	FString RecordDataFileName;

	// ���·��
	FString RelativePath;

};