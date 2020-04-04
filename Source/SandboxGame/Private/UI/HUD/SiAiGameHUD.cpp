// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiGameHUD.h"
#include "SSiAiGameHUDWidget.h"
#include "SWeakWidget.h"
#include "SiAiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SSiAiShortcutWidget.h"
#include "Player/SiAiPlayerState.h"
#include "Engine/GameViewportClient.h"
#include "SSiAiRayInfoWidget.h"
#include "SSiAiPointerWidget.h"
#include "SiAiPlayerController.h"



ASiAiGameHUD::ASiAiGameHUD()
{
	if (GEngine && GEngine->GameViewport)
	{
		SAssignNew(GameHUDWidget, SSiAiGameHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUDWidget.ToSharedRef()));
	}
}

void ASiAiGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<ASiAiGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;
	GM->InitGamePlayModule();
	// 绑定注册快捷栏容器
	GameHUDWidget->ShortcutWidget->RegisterShortcutContainer.BindUObject(GM->SPState, &ASiAiPlayerState::RegisterShortcutContainer);
	// 绑定注册射线信息文本事件
	GameHUDWidget->RayInfoWidget->RegisterRayInfoEvent.BindUObject(GM->SPState, &ASiAiPlayerState::RegisterRayInfoEvent);
	//绑定修改准星委托
	GM->SPController->UpdatePointer.BindRaw(GameHUDWidget->PointerWidget.Get(), &SSiAiPointerWidget::UpdatePointer);
}
