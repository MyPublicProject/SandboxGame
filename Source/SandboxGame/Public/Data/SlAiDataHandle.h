// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AiSiTypes.h"

class USoundCue;

/**
 * 
 */
class SANDBOXGAME_API SlAiDataHandle
{
public:
	
	SlAiDataHandle();
	
	static void Initialize();

	static TSharedPtr<SlAiDataHandle> Get();

	// 修改中英文
	void ChangeLocalizationCulture(ECultureTeam Culture);

	// 修改菜单音量
	void ResetMenuVolume(float MusicVal, float SoundVal);
	
	// 游戏数据初始化
	void InitializeGameData();

public:

	// 语言
	ECultureTeam CurrentCulture;

	// 音量
	float MusicVolume;
	float SoundVolume;

	// 存档数据
	TArray<FString> RecordDataList;

	// 存档名
	FString RecordName;

	// 物品属性
	TMap<int, TSharedPtr<ObjectAttribute>> ObjectAttrMap;

	// 物品贴图资源数组
	TArray<const FSlateBrush*> ObjectBrushList;

	// 资源属性图
	TMap<int, TSharedPtr<ResourceAttribute>> ResourceAttrMap;

	// GameModeData 是否初始化
	bool bIsGameData;

private:

	// 创建单例
	static TSharedRef<SlAiDataHandle> Create();

	// 根据 enum 类型获取字符串
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	// 根据字符串获取 Enum 值
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);

	// 初始化存档数据
	void InitRecordData();

	// 初始化 Menu 声音数据
	void InitializedMenuAudio();

	// 初始化物品属性
	void InitObjectAtte();

	// 初始化资源属性图
	void InitResourceAttrMap();

private:

	static TSharedPtr<SlAiDataHandle> DataInstance;

	// 保存 Menu 的声音
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;

	//获取MenuStyle,里面存放有声音文件
	const struct FSiAiMenuStyle *MenuStyle;

	//获取GameStyle
	const struct FSiAiGameStyle* GameStyle;

};
