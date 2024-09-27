// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include <Components/Image.h>
#include "StateWidget.generated.h"


/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API UStateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UEditableText> coinsNum;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> lifeNum;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> time;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> points;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> mario;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> coin;

	UFUNCTION()
	void UpdateCoin(int value);
	UFUNCTION()
	void UpdateLife(int value);
	UFUNCTION()
	void UpdateTime(int value);
	UFUNCTION()
	void UpdatePoints(int value);
};
