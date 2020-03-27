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

	//指定快捷栏的容器图标,把快捷栏的Style指定到Package
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush NormalContainerBrush;

	//指定被选择的容器的Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ChoosedContainerBrush;

	//指定没有颜色的Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush EmptyBrush;
	
	// 60号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_60;


	// 50号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_50;

	// 40号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_40;

	// 40号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_40;

	// 30号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_30;

	// 20号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_20;

	// 20号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_20;

	// 16号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_16;

	// 16号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_16;

	// 黑色颜色
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_White;

	// 白色颜色
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
