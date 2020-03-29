// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiGameHUD.h"
#include "SSiAiGameHUDWidget.h"
#include "SWeakWidget.h"
#include "SiAiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SSiAiShortcutWidget.h"
#include "Player/SiAiPlayerState.h"



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
	// °ó¶¨×¢²á¿ì½ÝÀ¸ÈÝÆ÷
	GameHUDWidget->ShortcutWidget->RegisterShortcutContainer.BindUObject(GM->SPState, &ASiAiPlayerState::RegisterShortcutContainer);
}
