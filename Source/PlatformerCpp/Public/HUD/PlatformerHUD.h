// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Widgets/StateWidget.h>
#include <Widgets/PointsWidget.h>
#include "PlatformerHUD.generated.h"



/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API APlatformerHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateWidgetClass")
	TSubclassOf<UStateWidget> stateWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateWidget")
	TObjectPtr<UStateWidget> stateWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidgetClass")
	TSubclassOf<UPointsWidget> pointsWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidget")
	TObjectPtr<UPointsWidget> pointsWidget;

	void CreateStateWidget();
	void UpdateCoins(int value);
	void UpdateLife(int value);
	void UpdateTime(int value);
	void UpdatePoints(int value);
};
