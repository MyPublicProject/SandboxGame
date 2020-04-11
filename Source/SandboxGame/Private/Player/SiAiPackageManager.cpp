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
	// �����ҵ�ָ�������
	for (TArray<TSharedPtr<SSiAiContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; It++) 
	{
		// ��ȡ����
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		// �ж����λ���Ƿ��������ڣ��ڵĻ�ֱ�ӷ����������
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y)
		{
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSiAiContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) {
		// ��ȡ����
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		// �ж����λ���Ƿ���������,�ڵĻ�ֱ�ӷ����������
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSiAiContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		// ��ȡ����
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		// �ж����λ���Ƿ���������,�ڵĻ�ֱ�ӷ����������
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	FVector2D StartPos = PackGeo.AbsoluteToLocal(OutputContainer->GetCachedGeometry().AbsolutePosition);
	FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
	// �ж����λ���Ƿ���������,�ڵĻ�ֱ�ӷ����������
	if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
		return OutputContainer;
	}

	// ���û����ĳ�����򷵻ؿ�
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
	// ��ȡ��ͣ������
	TSharedPtr<SSiAiContainerBaseWidget> CurrHoveredCon = LocateContainer(MousePos, PackGeo);
	// �����������
	if (CurrHoveredCon.IsValid())
	{
		// ���õ�ǰ������ͣ��ʾ
		CurrHoveredCon->UpdateHovered(true);
		// ���������һ�������������뵱ǰ��������ͬ
		if (LastHoveredCon.IsValid() && LastHoveredCon.Get() != CurrHoveredCon.Get())
		{
			// ����״̬
			LastHoveredCon->UpdateHovered(false);
		}
	}
	else
	{
		// ��ǰ��������������һ���������ڣ�ȡ����һ��������ͣ��ʾ
		if (LastHoveredCon.IsValid())
		{
			LastHoveredCon->UpdateHovered(false);
		}
	}

	//������һ��ͣ����
	LastHoveredCon = CurrHoveredCon;
}

void SiAiPackageManager::LeftOption(FVector2D MousePos, FGeometry PackGeo)
{
	// �Ȼ�ȡ���������
	TSharedPtr<SSiAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);

	// ����������ڣ�ִ�������¼�
	if (ClickedContainer.IsValid())
	{
		ClickedContainer->LeftOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
	// �������������
	if (!ClickedContainer.IsValid() && ObjectIndex != 0)
	{
		// ����Ʒ����
		// ������Ʒ
		ObjectIndex = ObjectNum = 0;
	}
}

void SiAiPackageManager::RightOption(FVector2D MousePos, FGeometry PackGeo)
{
	//�Ȼ�ȡ���������
	TSharedPtr<SSiAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);

	//�����������,ִ�������¼�
	if (ClickedContainer.IsValid()) {
		ClickedContainer->RightOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
}
