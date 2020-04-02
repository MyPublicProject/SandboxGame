// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiResourceRock.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"




ASiAiResourceRock::ASiAiResourceRock()
{
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_02.SM_Env_Rock_02'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_03.SM_Env_Rock_03'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_03_Snow.SM_Env_Rock_03_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_04.SM_Env_Rock_04'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Rock_04_Snow.SM_Env_Rock_04_Snow'"));

	// 随机数
	FRandomStream Stream;
	// 产生随机种子
	Stream.GenerateNewSeed();

	int RandIndex = Stream.RandRange(0, ResourcePath.Num() - 1);

	// 给模型组件添加上模型，这里不能用静态变量
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(*ResourcePath[RandIndex]);
	// 绑定模型到 Mesh 组件
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	ResourceIndex = 2;
}
