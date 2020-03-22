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
