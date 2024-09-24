// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlatformerController.h"
#include "Kismet/GameplayStatics.h"
#include <HUD/PlatformerHUD.h>

APlatformerController::APlatformerController()
{
	coins = 0;
	lives = 2;
	time = 100;
}

void APlatformerController::AddCoins(int value, FVector location)
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), coinSound, FVector(0.f, 0.f, 0.f));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), coinPartic, location);
	
	coins += value;
	curHUD->UpdateCoins(coins);
	if (coins>=100)
	{
		lives++;
		UpdateLives(1);
		coins -= 100;
		curHUD->UpdateCoins(coins);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), lifeSound, FVector(0.f, 0.f, 0.f));
	}
}

void APlatformerController::UpdateTime()
{
	time -= 1;
	curHUD->UpdateTime(time);

}


void APlatformerController::UpdatePoints(int value)
{
	points += value;
	curHUD->UpdatePoints(points);
}

void APlatformerController::UpdateLives(int value)
{
	lives += value;
	curHUD->UpdateLife(lives);
	
}

void APlatformerController::BeginPlay()
{
	Super::BeginPlay();
	curHUD = Cast<APlatformerHUD>(GetHUD());
	curHUD->CreateStateWidget();
	curHUD->UpdateCoins(coins);
	curHUD->UpdateLife(lives);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlatformerController::UpdateTime, 1.0f, true);
}
