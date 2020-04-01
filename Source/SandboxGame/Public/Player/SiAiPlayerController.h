// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AiSiTypes.h"
#include "SiAiPlayerController.generated.h"

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

protected:

	//角色指针
	class ASiAiPlayerCharacter *SPCharacter;

	class ASiAiPlayerState *SPState;

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

private:

	//左键预动作
	EUpperBody::Type LeftUpperType;

	//右键预动作
	EUpperBody::Type RightUpperType;

	//是否按住左右鼠标键
	bool IsLeftButtonDown;
	bool IsRightButtonDown;
	
};
