// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerState.h"
#include "AiSiTypes.h"
#include "STextBlock.h"




ASiAiPlayerState::ASiAiPlayerState()
{

}

void ASiAiPlayerState::RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock)
{
	for (TArray<TSharedPtr<ShortcutContainer>>::TIterator It(*ContainerList); It;It++)
	{
		ShortcutContainerList.Add(*It);
	}
	ShortcutInfoTextAttr.BindUObject(this, &ASiAiPlayerState::GetShortcutInfoText);
	// 绑定快捷栏信息TextBolck
	ShortcutInfoTextBlock->SetText(ShortcutInfoTextAttr);

	////临时测试代码,设置快捷栏的物品
	ShortcutContainerList[1]->SetObject(1)->SetObjectNum(5);
	ShortcutContainerList[2]->SetObject(2)->SetObjectNum(15);
	ShortcutContainerList[3]->SetObject(3)->SetObjectNum(1);
	ShortcutContainerList[4]->SetObject(4)->SetObjectNum(35);
	ShortcutContainerList[5]->SetObject(5)->SetObjectNum(45);
	ShortcutContainerList[6]->SetObject(6)->SetObjectNum(55);
	ShortcutContainerList[7]->SetObject(7)->SetObjectNum(64);
}

FText ASiAiPlayerState::GetShortcutInfoText() const
{
	return FText::FromString("666");
}
