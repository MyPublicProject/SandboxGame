// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiHandNone.h"
#include "Components/BoxComponent.h"


ASiAiHandNone::ASiAiHandNone()
{
	//不用绑定模型

	//设置碰撞盒属性
	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void ASiAiHandNone::BeginPlay()
{
	Super::BeginPlay();

	//定义物品序号
	ObjectIndex = 0;
}
