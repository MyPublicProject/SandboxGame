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

	// 提供给 ShortcutContainer 的添加快捷栏容器委托
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);
	
private:

	// 获取快捷栏物品信息
	FText GetShortcutInfoText() const;

private:

	//快捷栏序列
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	// 快捷栏信息参数
	TAttribute<FText> ShortcutInfoTextAttr;
	
};
