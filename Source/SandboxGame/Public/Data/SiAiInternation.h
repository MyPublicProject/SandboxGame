// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SANDBOXGAME_API SiAiInternation
{
public:
	static void Register(FText Value) {
		return;
	}
};

#define LOCTEXT_NAMESPACE "SiAiMenu"

SiAiInternation::Register(LOCTEXT("Menu", "Menu"));//菜单
SiAiInternation::Register(LOCTEXT("StartGame", "StartGame"));//开始游戏
SiAiInternation::Register(LOCTEXT("GameOption", "GameOption"));//游戏设置
SiAiInternation::Register(LOCTEXT("QuitGame", "QuitGame"));//退出游戏

SiAiInternation::Register(LOCTEXT("NewGame", "NewGame"));//新游戏
SiAiInternation::Register(LOCTEXT("LoadRecord", "LoadRecord"));//加载存档

SiAiInternation::Register(LOCTEXT("ChooseRecord", "ChooseRecord"));//选择存档

																   //进入游戏界面
SiAiInternation::Register(LOCTEXT("RecordName", "RecordName"));//存档名
SiAiInternation::Register(LOCTEXT("EnterGame", "EnterGame"));//进入游戏
SiAiInternation::Register(LOCTEXT("EnterRecord", "EnterRecord"));//进入存档
SiAiInternation::Register(LOCTEXT("RecordNameHint", "Input Record Name");//输入存档名
SiAiInternation::Register(LOCTEXT("NameRepeatedHint", "Record Name Repeated");//输入存档名

																			   //游戏设置界面
SiAiInternation::Register(LOCTEXT("Chinese", "Chinese"));//中文
SiAiInternation::Register(LOCTEXT("English", "English"));//英文
SiAiInternation::Register(LOCTEXT("Music", "Music"));//音乐
SiAiInternation::Register(LOCTEXT("Sound", "Sound"));//音效

													 //公用
SiAiInternation::Register(LOCTEXT("GoBack", "GoBack"));//返回

#undef LOCTEXT_NAMESPACE
