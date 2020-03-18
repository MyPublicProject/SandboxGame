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

	// ע�� Wideget ��ʽ
	static TSharedPtr<class FSlateStyleSet> Create();

	// ���ܷŽ����캯������
	static TSharedPtr<FSlateStyleSet> SiAiStyleInstance;

};
