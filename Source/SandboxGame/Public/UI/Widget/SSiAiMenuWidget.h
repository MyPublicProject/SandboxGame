// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AiSiTypes.h"

class SBox;
class STextBlock;
class SVerticalBox;
/**
 * 
 */
class SANDBOXGAME_API SSiAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSiAiMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	// 绑定各个 MenuItem 的方法
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	// 修改语言	
	void ChangeCulture(ECultureTeam Culture);
	// 修改音量
	void ChangeVolume(const float MusicVolume, const float SoundVolume);

private:
	// 保存根节点
	TSharedPtr<SBox> RootSizeBox;
	// 获取 MenuStyle
	const struct FSiAiMenuStyle *MenuStyle;
	// 保存标题
	TSharedPtr<STextBlock> TitleText;
	// 用来保存垂直列表
	TSharedPtr<SVerticalBox> ContentBox;
};
