// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block/BlockBase.h"
#include <Item/CoinBlock.h>
#include <Widgets/UI/Points.h>
#include "BlocCoin.generated.h"



/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API ABlocCoin : public ABlockBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin")
	TObjectPtr<ACoinBlock> coin;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin")
	TSubclassOf<ACoinBlock> coinClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidgetClass")
	TSubclassOf<APoints> pointsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidget")
	TObjectPtr<APoints> pointsWidget;

	void HitBlock_Implementation() override;
};
