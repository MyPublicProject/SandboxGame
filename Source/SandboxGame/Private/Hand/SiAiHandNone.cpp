// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiHandNone.h"
#include "Components/BoxComponent.h"


ASiAiHandNone::ASiAiHandNone()
{
	//���ð�ģ��

	//������ײ������
	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void ASiAiHandNone::BeginPlay()
{
	Super::BeginPlay();

	//������Ʒ���
	ObjectIndex = 0;
}
