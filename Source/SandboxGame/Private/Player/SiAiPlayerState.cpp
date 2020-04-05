// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerState.h"
#include "AiSiTypes.h"
#include "STextBlock.h"
#include "SlAiDataHandle.h"




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

void ASiAiPlayerState::ChooseShortcut(bool IsPre)
{
	// 下一个被选中的下标
	int NextIndex = 0;
	if (IsPre)
	{
		NextIndex = CurrentShortcutIndex - 1 < 0 ? 8 : CurrentShortcutIndex - 1;
	}
	else
	{
		NextIndex = CurrentShortcutIndex + 1 > 8 ? 0 : CurrentShortcutIndex + 1;
	}

	ShortcutContainerList[CurrentShortcutIndex]->SetChoosed(false);
	ShortcutContainerList[NextIndex]->SetChoosed(true);

	// 更新当前选择的容器
	CurrentShortcutIndex = NextIndex;
}

int ASiAiPlayerState::GetCurrentHandObjectIndex() const
{
	if (ShortcutContainerList.Num() == 0) return 0;
	return ShortcutContainerList[CurrentShortcutIndex]->ObjectIndex;
}

EObjectType::Type ASiAiPlayerState::GetCurrentObjectType()
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	return ObjectAttr->ObjectType;
}

void ASiAiPlayerState::RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock)
{
	RayInfoTextAttr.BindUObject(this, &ASiAiPlayerState::GetRayInfoText);
	//绑定射线检测信息
	RayInfoTextBlock->SetText(RayInfoTextAttr);
}

int ASiAiPlayerState::GetAffectRange()
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	//获取当前手上物品的作用范围
	return ObjectAttr->AffectRange;
}

int ASiAiPlayerState::GetDamageValue(EResourceType::Type ResourceType)
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	switch (ResourceType)
	{
	case EResourceType::Plant:
		return ObjectAttr->PlantAttack;
		break;
	case EResourceType::Metal:
		return ObjectAttr->MetalAttcck;
		break;
	case EResourceType::Animal:
		return ObjectAttr->AnimalAttack;
		break;
	}
	return ObjectAttr->PlantAttack;
}

FText ASiAiPlayerState::GetShortcutInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ObjectAttr->EN;
		break;
	case ECultureTeam::ZH:
		return ObjectAttr->ZH;
		break;
	default:
		break;
	}
	return ObjectAttr->ZH;
}

FText ASiAiPlayerState::GetRayInfoText() const
{
	return RayInfoText;
}
