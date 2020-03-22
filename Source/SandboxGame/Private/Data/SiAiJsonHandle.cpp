// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiJsonHandle.h"
#include "FileHelper.h"
#include "Common/SiAiHelper.h"
#include "Paths.h"

SiAiJsonHandle::SiAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");

	RelativePath = FString("Res/ConfigData/");
}

void SiAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
		//获取数据
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));
		//获取存档数据
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));
		for (int i = 0; i < RecordDataArray.Num(); ++i) {
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
		}
	}
	else {
		SiAiHelper::Debug(FString("Deserialize Failed"));
	}
}

bool SiAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		// 获取绝对路径
		// FString AbsoPath = FPaths::GameContentDir() + RelaPath + FileName;
		FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsoPath))
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsoPath))
			{
				return true;
			}
			else
			{
				// 加载不成功
				SiAiHelper::Debug(FString("Load Error") + AbsoPath);
			}
		}
		else
		{
			// 输出文件不存在
			SiAiHelper::Debug(FString("File Not Exist") = AbsoPath);
		}
	}
	return false;
}
