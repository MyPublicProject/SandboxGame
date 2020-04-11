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

	// �������
	void InsertContainer(TSharedPtr<class SSiAiContainerBaseWidget> Container, EContainerType::Type InserType);

	// ������ͣ��������ɫ
	void UpdateHovered(FVector2D MousePos, FGeometry PackGeo);

	// ����¼�,���������λ�ú�PackageWidget��Geometry
	void LeftOption(FVector2D MousePos, FGeometry PackGeo);

	// �Ҽ��¼�,���������λ�ú�PackageWidget��Geometry
	void RightOption(FVector2D MousePos, FGeometry PackGeo);

public:

	// �����ƷID
	int ObjectIndex;

	// �����Ʒ����
	int ObjectNum;

	// ������Ʒί��,�󶨵ķ�����PlayerState��PlayerThrowObject
	FThrowObject PlayerThrowObject;
	// �޸Ŀ������Ϣί��
	FPackShortChange ChangeHandObject;

private:

	// ����ʵ������
	static TSharedPtr<SiAiPackageManager> Create();

	// ��ȡ���ָ�������
	TSharedPtr<SSiAiContainerBaseWidget> LocateContainer(FVector2D MousePos, FGeometry PackGeo);

	// ������Ʒ�¼�
	void ThrowObject(int ObjectID, int Num);

	// �ϳ���ȡ�¼�
	void CompoundOutput(int ObjectID, int Num);

	// �ϳ������¼�
	void CompoundInput();

	// ������任�¼�
	void PackShortChange(int ShortcutID, int ObjectID, int ObjectNum);
private:

	// ����ָ��
	static TSharedPtr<SiAiPackageManager> PackageInstance;

	// �����б�
	TArray<TSharedPtr<SSiAiContainerBaseWidget>> InputContainerList;
	TArray<TSharedPtr<SSiAiContainerBaseWidget>> NormalContainerList;
	TArray<TSharedPtr<SSiAiContainerBaseWidget>> ShortcutContainerList;
	// �������ֻ��һ��
	TSharedPtr<SSiAiContainerBaseWidget> OutputContainer;

	// ��һ����ͣ������
	TSharedPtr<SSiAiContainerBaseWidget> LastHoveredCon;

};
