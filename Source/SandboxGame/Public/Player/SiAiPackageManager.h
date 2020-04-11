// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AiSiTypes.h"
#include "SSiAiContainerBaseWidget.h"

/**
 * 
 */
class SANDBOXGAME_API SiAiPackageManager
{

public:

	SiAiPackageManager();

	static void Initialize();

	static TSharedPtr<SiAiPackageManager> Get();

	// 添加容器
	void InsertContainer(TSharedPtr<class SSiAiContainerBaseWidget> Container, EContainerType::Type InserType);

	// 更新悬停的容器颜色
	void UpdateHovered(FVector2D MousePos, FGeometry PackGeo);

	// 左键事件,参数是鼠标位置和PackageWidget的Geometry
	void LeftOption(FVector2D MousePos, FGeometry PackGeo);

	// 右键事件,参数是鼠标位置和PackageWidget的Geometry
	void RightOption(FVector2D MousePos, FGeometry PackGeo);

public:

	// 鼠标物品ID
	int ObjectIndex;

	// 鼠标物品数量
	int ObjectNum;

private:

	// 创建实例方法
	static TSharedPtr<SiAiPackageManager> Create();

	// 获取鼠标指向的容器
	TSharedPtr<SSiAiContainerBaseWidget> LocateContainer(FVector2D MousePos, FGeometry PackGeo);
private:

	// 单例指针
	static TSharedPtr<SiAiPackageManager> PackageInstance;

	// 容器列表
	TArray<TSharedPtr<SSiAiContainerBaseWidget>> InputContainerList;
	TArray<TSharedPtr<SSiAiContainerBaseWidget>> NormalContainerList;
	TArray<TSharedPtr<SSiAiContainerBaseWidget>> ShortcutContainerList;
	// 输出容器只有一个
	TSharedPtr<SSiAiContainerBaseWidget> OutputContainer;

	// 上一个悬停的容器
	TSharedPtr<SSiAiContainerBaseWidget> LastHoveredCon;

};
