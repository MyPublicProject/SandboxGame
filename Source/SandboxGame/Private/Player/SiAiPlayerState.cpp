// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPlayerState.h"
#include "AiSiTypes.h"
#include "STextBlock.h"
#include "SlAiDataHandle.h"




ASiAiPlayerState::ASiAiPlayerState()
{
	// 允许每贞运行
	PrimaryActorTick.bCanEverTick = true;
	//设置初始血值为500
	HP = 500.f;
	//设置初始饥饿值为600
	Hunger = 600.f;
}

void ASiAiPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 如果解饿度为零，持续减血
	if (Hunger <= 0)
	{
		HP -= DeltaSeconds * 2;
	}
	else
	{
		if (true)
		{
			//如果饥饿不为0,持续减饥饿度,每秒减2
			Hunger -= DeltaSeconds * 2;

			//持续加血,每秒加1
			HP += DeltaSeconds;
		}
	}

	//设定范围
	HP = FMath::Clamp<float>(HP, 0.f, 500.f);
	Hunger = FMath::Clamp<float>(Hunger, 0.f, 600.f);

	//执行修改玩家状态UI的委托
	UpdateStateWidget.ExecuteIfBound(HP / 500.f, Hunger / 500.f);
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
