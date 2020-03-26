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
	class ASiAiPlayerCharacter* SPCharacter;

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
	
};
