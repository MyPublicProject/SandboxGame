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

private:

	// 读取 Json 文件到字符串
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

private:

	// 存档文件名
	FString RecordDataFileName;

	// 相对路径
	FString RelativePath;

};