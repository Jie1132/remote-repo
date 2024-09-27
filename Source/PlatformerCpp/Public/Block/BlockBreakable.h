// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block/BlockBase.h"
#include <Widgets/PointsWidget.h>
#include <Widgets/UI/Points.h>
#include "BlockBreakable.generated.h"



/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API ABlockBreakable : public ABlockBase
{
	GENERATED_BODY()
public:

	

	void HitBlock_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidgetClass")
	TSubclassOf<APoints> pointsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidget")
	TObjectPtr<APoints> pointsWidget;
};
