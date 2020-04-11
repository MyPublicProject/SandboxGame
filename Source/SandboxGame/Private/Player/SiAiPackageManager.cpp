// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiPackageManager.h"

TSharedPtr<SiAiPackageManager> SiAiPackageManager::PackageInstance = NULL;

SiAiPackageManager::SiAiPackageManager()
{
	ObjectIndex = 3;
	ObjectNum = 35;
}

void SiAiPackageManager::Initialize()
{
	if (!PackageInstance.IsValid())
	{
		PackageInstance = Create();
	}
}

TSharedPtr<SiAiPackageManager> SiAiPackageManager::Get()
{
	Initialize();
	return PackageInstance;
}

TSharedPtr<SiAiPackageManager> SiAiPackageManager::Create()
{
	TSharedPtr<SiAiPackageManager> PackageRef = MakeShareable(new SiAiPackageManager());
	return PackageRef;
}

TSharedPtr<SSiAiContainerBaseWidget> SiAiPackageManager::LocateContainer(FVector2D MousePos, FGeometry PackGeo)
{
	// 迭代找到指向的容器
	for (TArray<TSharedPtr<SSiAiContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; It++) 
	{
		// 获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		// 判断鼠标位置是否在区域内，在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y)
		{
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSiAiContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) {
		// 获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		// 判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSiAiContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		// 获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		// 判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	FVector2D StartPos = PackGeo.AbsoluteToLocal(OutputContainer->GetCachedGeometry().AbsolutePosition);
	FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
	// 判断鼠标位置是否在区域内,在的话直接返回这个容器
	if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
		return OutputContainer;
	}

	// 如果没有在某个区域返回空
	return nullptr;
}

void SiAiPackageManager::InsertContainer(TSharedPtr<class SSiAiContainerBaseWidget> Container, EContainerType::Type InserType)
{
	switch (InserType)
	{
	case EContainerType::Output:
		OutputContainer = Container;
		break;
	case EContainerType::Input:
		InputContainerList.Add(Container);
		break;
	case EContainerType::Normal:
		NormalContainerList.Add(Container);
		break;
	case EContainerType::Shortcut:
		ShortcutContainerList.Add(Container);
		break;
	}
}

void SiAiPackageManager::UpdateHovered(FVector2D MousePos, FGeometry PackGeo)
{
	// 获取悬停的容器
	TSharedPtr<SSiAiContainerBaseWidget> CurrHoveredCon = LocateContainer(MousePos, PackGeo);
	// 如果容器存在
	if (CurrHoveredCon.IsValid())
	{
		// 设置当前容器悬停显示
		CurrHoveredCon->UpdateHovered(true);
		// 如果存在上一个容器，并且与当前容器不相同
		if (LastHoveredCon.IsValid() && LastHoveredCon.Get() != CurrHoveredCon.Get())
		{
			// 更新状态
			LastHoveredCon->UpdateHovered(false);
		}
	}
	else
	{
		// 当前容器不存在切上一个容器存在，取消上一容器的悬停显示
		if (LastHoveredCon.IsValid())
		{
			LastHoveredCon->UpdateHovered(false);
		}
	}

	//更新上一悬停容器
	LastHoveredCon = CurrHoveredCon;
}

void SiAiPackageManager::LeftOption(FVector2D MousePos, FGeometry PackGeo)
{
	// 先获取点击的容器
	TSharedPtr<SSiAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);

	// 如果容器存在，执行容器事件
	if (ClickedContainer.IsValid())
	{
		ClickedContainer->LeftOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
	// 如果容器不存在
	if (!ClickedContainer.IsValid() && ObjectIndex != 0)
	{
		// 把物品丢弃
		// 重置物品
		ObjectIndex = ObjectNum = 0;
	}
}

void SiAiPackageManager::RightOption(FVector2D MousePos, FGeometry PackGeo)
{
	//先获取点击的容器
	TSharedPtr<SSiAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);

	//如果容器存在,执行容器事件
	if (ClickedContainer.IsValid()) {
		ClickedContainer->RightOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
}
