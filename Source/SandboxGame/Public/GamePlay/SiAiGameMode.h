// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SiAiGameMode.generated.h"

// ��ʼ������������ί��
DECLARE_DELEGATE(FInitPackageManager)
/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ASiAiGameMode();

	virtual void Tick(float DeltaSeconds) override;

	// �����ֵ����GameHUD���ã��������������ı���
	void InitGamePlayModule();

public:

	class ASiAiPlayerController *SPController;

	class ASiAiPlayerCharacter *SPCharacter;

	class ASiAiPlayerState *SPState;

	// ��ʼ����������ί��,�󶨵ķ�����PackageWidget��InitPackageManager����
	FInitPackageManager InitPackageManager;

protected:

	virtual void BeginPlay() override;

	// ��ʼ������������
	void InitializePackage();

private:

	// �Ƿ��Ѿ���ʼ������
	bool IsInitPackage;
	
	
};
