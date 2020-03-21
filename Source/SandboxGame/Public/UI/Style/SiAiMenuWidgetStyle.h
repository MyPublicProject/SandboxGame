// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateFontInfo.h"
#include "NoExportTypes.h"

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

	// 指定 MenuHUD 背景图片
	UPROPERTY(EditAnywhere, Category = MenuHUD)
		FSlateBrush MenuHUDBackgroundBrush;

	// 指定 Menu 背景图片
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush MenuBackgroundBrush;

	// Menu左边的图标Brush
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush LeftIconBrush;

	// Menu右边的图标Brush
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush RightIconBrush;

	// Menu标题Border的Brush
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush TitleBorderBrush;

	// MenuItem 的 Bush
	UPROPERTY(EditAnywhere, Category = MenuItem)
		FSlateBrush MenuItemBrush;

	// 60 号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_60;

	// 40 号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_40;

	// 30 号字体
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_30;

	// 黑色
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_White;

	// 白色
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_Black;

	// GameSet 的背景
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush GameOptionBGBrush;

	// CheckedBox 的 Brush 被选中
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush CheckedBoxBrush;
		// CheckedBox 的 Brush 不被选中
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush UnCheckedBoxBrush;
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
