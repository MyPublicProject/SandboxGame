// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AiSiTypes.h"

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

public:

	ECultureTeam CurrentCulture;

private:

	//��������
	static TSharedRef<SlAiDataHandle> Create();

private:

	static TSharedPtr<SlAiDataHandle> DataInstance;

};
