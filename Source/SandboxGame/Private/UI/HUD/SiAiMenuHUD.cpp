// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiMenuHUD.h"
#include "SlateBasics.h"
#include "SSiAiMeunHUDWidget.h"




ASiAiMenuHUD::ASiAiMenuHUD()
{
	if (GEngine && GEngine->GameViewport) {
		SAssignNew(MenuHUDWidget, SSiAiMeunHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));
	}
}
