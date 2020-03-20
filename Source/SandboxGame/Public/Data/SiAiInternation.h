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

SiAiInternation::Register(LOCTEXT("Menu", "Menu"));//�˵�
SiAiInternation::Register(LOCTEXT("StartGame", "StartGame"));//��ʼ��Ϸ
SiAiInternation::Register(LOCTEXT("GameOption", "GameOption"));//��Ϸ����
SiAiInternation::Register(LOCTEXT("QuitGame", "QuitGame"));//�˳���Ϸ

SiAiInternation::Register(LOCTEXT("NewGame", "NewGame"));//����Ϸ
SiAiInternation::Register(LOCTEXT("LoadRecord", "LoadRecord"));//���ش浵

SiAiInternation::Register(LOCTEXT("ChooseRecord", "ChooseRecord"));//ѡ��浵

																   //������Ϸ����
SiAiInternation::Register(LOCTEXT("RecordName", "RecordName"));//�浵��
SiAiInternation::Register(LOCTEXT("EnterGame", "EnterGame"));//������Ϸ
SiAiInternation::Register(LOCTEXT("EnterRecord", "EnterRecord"));//����浵
SiAiInternation::Register(LOCTEXT("RecordNameHint", "Input Record Name");//����浵��
SiAiInternation::Register(LOCTEXT("NameRepeatedHint", "Record Name Repeated");//����浵��

																			   //��Ϸ���ý���
SiAiInternation::Register(LOCTEXT("Chinese", "Chinese"));//����
SiAiInternation::Register(LOCTEXT("English", "English"));//Ӣ��
SiAiInternation::Register(LOCTEXT("Music", "Music"));//����
SiAiInternation::Register(LOCTEXT("Sound", "Sound"));//��Ч

													 //����
SiAiInternation::Register(LOCTEXT("GoBack", "GoBack"));//����

#undef LOCTEXT_NAMESPACE
