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

	// �޸Ĳ˵�����
	void ResetMenuVolume(float MusicVal, float SoundVal);

public:

	// ����
	ECultureTeam CurrentCulture;
	// ����
	float MusicVolume;
	float SoundVolume;

private:

	//��������
	static TSharedRef<SlAiDataHandle> Create();

private:

	static TSharedPtr<SlAiDataHandle> DataInstance;

};
