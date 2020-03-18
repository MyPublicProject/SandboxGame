// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "SiAiMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SANDBOXGAME_API FSiAiMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSiAiMenuStyle();
	virtual ~FSiAiMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSiAiMenuStyle& GetDefault();

	// ָ�� MenuHUD ����ͼƬ
	UPROPERTY(EditAnywhere, Category = MenuHUD)
		FSlateBrush MenuHUDBackgroundBrush;

	// ָ�� Menu ����ͼƬ
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush MenuBackgroundBrush;

	// Menu��ߵ�ͼ��Brush
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush LeftIconBrush;

	// Menu�ұߵ�ͼ��Brush
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush RightIconBrush;

	// Menu����Border��Brush
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush TitleBorderBrush;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USiAiMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSiAiMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
