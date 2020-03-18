// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SANDBOXGAME_API SiAiStyle
{
public:
	
	static void Initialze();

	static FName GetStyleSetName();

	static void ShutDown();

	static const ISlateStyle& Get();

private:

	// 注册 Wideget 样式
	static TSharedPtr<class FSlateStyleSet> Create();

	// 不能放进构造函数里面
	static TSharedPtr<FSlateStyleSet> SiAiStyleInstance;

};
