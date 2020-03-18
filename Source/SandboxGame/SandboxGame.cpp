// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxGame.h"
#include "Modules/ModuleManager.h"
#include "SiAiStyle.h"
#include "SlateStyleRegistry.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FSiAiCourceModule, SandboxGame, "SandboxGame" );

void FSiAiCourceModule::StartupModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(SiAiStyle::GetStyleSetName());
	SiAiStyle::Initialze();
}

void FSiAiCourceModule::ShutdownModule()
{
	SiAiStyle::ShutDown();
}
