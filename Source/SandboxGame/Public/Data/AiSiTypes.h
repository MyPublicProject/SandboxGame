// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "Engine/Engine.h"

/**
 * 
 */
UENUM()// UE4反射
enum class ECultureTeam :uint8 {
	EN = 0,
	ZH
};

// Menu按钮的类型 // 普通枚举
namespace EMenuItem
{
	enum Type
	{
		None,
		StartGame,
		GameOption,
		QuitGame,
		NewGame,
		LoadRecord,
		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord
	};
}

// Menu界面类型
namespace EMenuType
{
	enum Type
	{
		None,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

// Menu 动画状态枚举
namespace EMenuAnim
{
	enum Type
	{
		Stop, // 停止动画
		Close, // 关闭 Menu
		Open, // 打开 Menu
	};
}

// 视角模式
namespace EGameViewMode 
{
	enum Type
	{
		First,
		Third
	};
}

// 上半身动画状态
namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,
		Hit,
		Fight,
		PickUp,
		Eat,
	};
}

//物品类型
namespace EObjectType
{
	enum Type
	{
		Normal = 0,//普通物品,木头,石头
		Food,//食物,苹果,肉
		Tool,//工具,锤子,斧子
		Weapon//武器,剑
	};
}

// 物品属性结构
struct ObjectAttribute
{
	FText EN;//英文名
	FText ZH;//中文名
	EObjectType::Type ObjectType;//物品类型
	int PlantAttack;//对植物的攻击力
	int MetalAttcck;//对金属资源的攻击力
	int AnimalAttack;//对动物的攻击力
	int AffectRange;//攻击距离
	FString TexPath;//图片路径
	//构造函数
	ObjectAttribute(const FText ENName, const FText ZHName, const EObjectType::Type OT, const int PA, const int MA, const int AA, const int AR, const FString TP) {
		EN = ENName;
		ZH = ZHName;
		ObjectType = OT;
		PlantAttack = PA;
		MetalAttcck = MA;
		AnimalAttack = AA;
		AffectRange = AR;
		TexPath = TP;
	}
};

// 快捷栏容器结构体
struct ShortcutContainer
{
	// 物品 ID
	int ObjectIndex;
	int ObjectNum;
	TSharedPtr<SBorder> ContainerBorder;
	TSharedPtr<SBorder> ObjectImage;
	TSharedPtr<STextBlock> ObjectNumText;
	const FSlateBrush *NormalContainerBrush;
	const FSlateBrush *ChoosedContainerBrush;
	TArray<const FSlateBrush*> ObjectBrushList;

	ShortcutContainer(TSharedPtr<SBorder> CB, TSharedPtr<SBorder> OI, TSharedPtr<STextBlock> ONT, const FSlateBrush* NCB, const FSlateBrush* CCB, TArray<const FSlateBrush*> OBL)
	{
		ContainerBorder = CB;
		ObjectImage = OI;
		ObjectNumText = ONT;
		NormalContainerBrush = NCB;
		ChoosedContainerBrush = CCB;
		ObjectBrushList = OBL;

		//初始化显示设置
		ObjectIndex = 0;
		ObjectNum = 0;
		ContainerBorder->SetBorderImage(NormalContainerBrush);
		ObjectImage->SetBorderImage(ObjectBrushList[0]);
	}

	// 设置是否选中当前物品， True 是要选中， 返回物品类型
	int SetChoosed(bool Option)
	{
		if (Option)
		{
			ContainerBorder->SetBorderImage(ChoosedContainerBrush);
		}
		else
		{
			ContainerBorder->SetBorderImage(NormalContainerBrush);
		}
		return ObjectIndex;
	}

	// 设置 Index
	ShortcutContainer *SetObject(int NewIndex)
	{
		ObjectIndex = NewIndex;
		// GEngine->AddOnScreenDebugMessage(-1, 100.0, FColor::Red, FString::FromInt(ObjectIndex));
		ObjectImage->SetBorderImage(ObjectBrushList[ObjectIndex]);
		return this;
	}

	// 设置数量
	ShortcutContainer *SetObjectNum(int Num = 0)
	{
		ObjectNum = Num;
		// 如果数量为 0 或 1， 不显示数字
		if (ObjectNum == 0 || ObjectNum == 1)
		{
			ObjectNumText->SetText(FString(""));
		}
		else
		{
			ObjectNumText->SetText(FString::FromInt(ObjectNum));
		}
		return this;
	}
};

// 资源类型
namespace EResourceType {
	enum Type
	{
		Plant = 0,
		Metal,
		Animal
	};
}

// 资源属性结构体
struct ResourceAttribute
{
	FText EN;// 英文名
	FText ZH;// 中文名
	EResourceType::Type ResourceType;
	int HP;
	TArray<TArray<int>> FlobObjectInfo;

	ResourceAttribute(const FText ENName, const FText ZHName, const EResourceType::Type RT, const int HPValue, TArray<TArray<int>>* FOI) {
		EN = ENName;
		ZH = ZHName;
		ResourceType = RT;
		HP = HPValue;

		//将数组元素迭代进本地数组
		for (TArray<TArray<int>>::TIterator It(*FOI); It; ++It) {
			TArray<int> FlobObjectInfoItem;
			for (TArray<int>::TIterator Ih(*It); Ih; ++Ih) {
				FlobObjectInfoItem.Add(*Ih);
			}
			FlobObjectInfo.Add(FlobObjectInfoItem);
		}
	}
};

// Game界面分类
namespace EGameUIType
{
	enum Type
	{
		Game,//游戏模式UI
		Pause,//暂停
		Lose,//输了,死亡
		Package,//背包
		ChatRoom//聊天室
	};
}

// 背包容器类型
namespace EContainerType
{
	enum Type
	{
		Output,//合成表输出
		Input,//合成表输入
		Normal,//普通容器
		Shortcut,//快捷栏容器
	};
}