// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateBrush.h"
#include "SlateFontInfo.h"

#include "SiAiGameWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SANDBOXGAME_API FSiAiGameStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSiAiGameStyle();
	virtual ~FSiAiGameStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSiAiGameStyle& GetDefault();

	//ָ�������������ͼ��,�ѿ������Styleָ����Package
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush NormalContainerBrush;

	//ָ����ѡ���������Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ChoosedContainerBrush;

	//ָ��û����ɫ��Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush EmptyBrush;
	
	// 60������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_60;


	// 50������������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_50;

	// 40������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_40;

	// 40������������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_40;

	// 30������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_30;

	// 20������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_20;

	// 20������������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_20;

	// 16������������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_16;

	// 16������
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_16;

	// ��ɫ��ɫ
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_White;

	// ��ɫ��ɫ
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_Black;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USiAiGameWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSiAiGameStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};