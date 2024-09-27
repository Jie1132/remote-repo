// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block/BlockBase.h"
#include <Item/BlockFlower.h>
#include <Widgets/UI/Points.h>
#include "BlockFireFlower.generated.h"


/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API ABlockFireFlower : public ABlockBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flower")
	TObjectPtr<ABlockFlower> flower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlowerClass")
	TSubclassOf<ABlockFlower> flowerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidgetClass")
	TSubclassOf<APoints> pointsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidget")
	TObjectPtr<APoints> pointsWidget;

	void HitBlock_Implementation() override;
};
