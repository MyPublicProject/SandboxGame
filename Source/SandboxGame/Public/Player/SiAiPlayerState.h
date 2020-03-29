// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Attribute.h"
#include "AiSiTypes.h"
#include "SiAiPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	ASiAiPlayerState();

	// �ṩ�� ShortcutContainer ����ӿ��������ί��
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);
	
private:

	// ��ȡ�������Ʒ��Ϣ
	FText GetShortcutInfoText() const;

private:

	//���������
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	// �������Ϣ����
	TAttribute<FText> ShortcutInfoTextAttr;
	
};
