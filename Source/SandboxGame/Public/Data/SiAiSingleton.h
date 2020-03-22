// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<class T>
class SANDBOXGAME_API SiAiSingleton
{
public:

	static TSharedPtr<T> Get();

private:

	static void Initialize();

	static TSharedRef<T> Create();

private:

	static TSharedPtr<T> TInstance;

};

template<class T>
TSharedPtr<T> SiAiSingleton<T>::TInstance = NULL;

template<class T>
TSharedRef<T> SiAiSingleton<T>::Create()
{
	TSharedRef<T> TRef = MakeShareable(new T());
	return TRef;
}

template<class T>
void SiAiSingleton<T>::Initialize()
{
	if (!TInstance.IsValid())
	{
		TInstance = Create();
	}
}

template<class T>
TSharedPtr<T> SiAiSingleton<T>::Get()
{
	Initialize();
	return TInstance;
}