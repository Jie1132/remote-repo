// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block/BlocCoin.h"
#include "BlockCoins.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API ABlockCoins : public ABlocCoin
{
	GENERATED_BODY()
public:
	int Counter;
	FTimerHandle TimerHandle;
	void HitBlock_Implementation() override;
	UFUNCTION()
	void IncrementCounter();
	UFUNCTION()
	void StopCounter();
	virtual void BeginPlay() override;


};
