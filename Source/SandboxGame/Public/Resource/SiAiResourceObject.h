// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiSiTypes.h"
#include "SiAiResourceObject.generated.h"

UCLASS()
class SANDBOXGAME_API ASiAiResourceObject : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASiAiResourceObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ��ȡ��Ʒ��Ϣ
	FText GetInfoText() const;

	// ��ȡ��Դ����
	EResourceType::Type GetResourceType();

	// ��ȡѪ���ٷֱ�
	float GetHPRange();

	// ��ȡ�˺�
	ASiAiResourceObject *TakeObjectDamage(int Damage);

public:

	// ��ԴID
	int ResourceIndex;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ���ɵ�����
	void CreateFlobObject();

protected:

	// �����
	USceneComponent *RootScene;

	// ��̬ģ��
	UStaticMeshComponent *BaseMesh;

	// ������Դ��ַ����
	TArray<FString> ResourcePath;

	// Ѫ��
	int HP;

	// ����Ѫ��
	int BaseHP;
	
};
