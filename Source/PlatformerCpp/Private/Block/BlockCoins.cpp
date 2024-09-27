// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockCoins.h"
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>
#include <PlatformerFunctionLibrary.h>

void ABlockCoins::HitBlock_Implementation()
{
	if (bIsBlock==false)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABlockCoins::IncrementCounter, 1.0f, true);
		bIsBlock = true;
	}
	
	if (Counter<10)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		APlatformerController* platformerController = Cast<APlatformerController>(playerController);
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), blockSound, blockParticle, GetActorLocation());
		FVector curLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100);
		pointsWidget = GetWorld()->SpawnActor<APoints>(pointsWidgetClass, curLocation, GetActorRotation());
		if (pointsWidget != nullptr)
		{
			pointsWidget->SetPoints(points);
		}
		coin = GetWorld()->SpawnActor<ACoinBlock>(coinClass, GetActorLocation(), GetActorRotation());
		if (coin != nullptr)
		{
			coin->UpdateCoins();
		}
		/*bIsBlock = true;*/
		if (platformerController != nullptr)
		{
			platformerController->UpdatePoints(points);
		}
	}
	else
	{
		cube->SetMaterial(0, blockMaterial);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABlockCoins::StopCounter, 0.1f, false);
	}
}

void ABlockCoins::IncrementCounter()
{
	Counter++;
}

void ABlockCoins::StopCounter()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ABlockCoins::BeginPlay()
{
	Super::BeginPlay();
	
}

