// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiGameHUD.h"
#include "SSiAiGameHUDWidget.h"
#include "SWeakWidget.h"


ASiAiGameHUD::ASiAiGameHUD()
{
	if (GEngine && GEngine->GameViewport)
	{
		SAssignNew(GameHUDWidget, SSiAiGameHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUDWidget.ToSharedRef()));
	}
}
