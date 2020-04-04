﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AiSiTypes.h"
#include "SiAiPlayerController.generated.h"


// 修改准星委托
DECLARE_DELEGATE_TwoParams(FUpdatePointer, bool, float)
// 显示UI委托
// DECLARE_DELEGATE_TwoParams(FShowGameUI, EGameUIType::Type, EGameUIType::Type)
// 修改小地图视野范围委托
// DECLARE_DELEGATE_OneParam(FUpdateMiniMapWidth, int)

/**
 * 
 */
UCLASS()
class SANDBOXGAME_API ASiAiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ASiAiPlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

	//对Character的手持物品进行更改,这个函数在playerstate内会调用
	void ChangeHandObject();

public:

	//角色指针
	class ASiAiPlayerCharacter *SPCharacter;

	class ASiAiPlayerState *SPState;

	// 实时修改准星的委托,注册的函数是PointerWidget的UpdatePointer
	FUpdatePointer UpdatePointer;
	// 显示游戏UI界面委托,绑定的方法是GameHUDWidget的ShowGameUI
	// FShowGameUI ShowGameUI;
	// 修改小地图视野范围委托,注册函数是SlAiSceneCapture2D的UpdateMiniMapWidth 
	// FUpdateMiniMapWidth UpdateMiniMapWidth;

protected:

	virtual void BeginPlay() override;

private:

	// 切换视角
	void ChangeView();

	// 鼠标按键事件
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();

	// 鼠标滚轮事件
	void ScrollUpEvent();
	void ScrollDownEvent();

	// 退出游戏
	void QuitGame();

	// 修改预动作
	void ChangePreUpperType(EUpperBody::Type RightType);

private:

	//左键预动作
	EUpperBody::Type LeftUpperType;

	//右键预动作
	EUpperBody::Type RightUpperType;

	//是否按住左右鼠标键
	bool IsLeftButtonDown;
	bool IsRightButtonDown;
	
};
