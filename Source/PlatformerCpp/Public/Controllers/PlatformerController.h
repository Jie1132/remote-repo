// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Sound/Soundbase.h"
#include "Particles/ParticleSystem.h"
#include <HUD/PlatformerHUD.h>
#include "PlatformerController.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API APlatformerController : public APlayerController
{
	GENERATED_BODY()
public:
	APlatformerController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinsNums")
	int coins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifeNums")
	int lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
	int points;

	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "CoinSound")
	TObjectPtr<USoundBase> coinSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DieSound")
	TObjectPtr<USoundBase> dieSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinPartic")
	TObjectPtr<UParticleSystem> coinPartic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DiePartic")

	TObjectPtr<UParticleSystem> diePartic;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "LifeSound")
	TObjectPtr<USoundBase> lifeSound;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "CurHud")
	TObjectPtr<APlatformerHUD> curHUD;
	UFUNCTION()
	void AddCoins(int value, FVector location);
	UFUNCTION()
	void UpdateTime();

	UFUNCTION()
	void UpdatePoints(int value);

	UFUNCTION()
	void UpdateLives(int value);

	virtual void BeginPlay();
};
