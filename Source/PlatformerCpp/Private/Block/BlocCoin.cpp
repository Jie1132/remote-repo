// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlocCoin.h"
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>
#include <PlatformerFunctionLibrary.h>

void ABlocCoin::HitBlock_Implementation()
{
	if (bIsBlock == false)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		APlatformerController* platformerController = Cast<APlatformerController>(playerController);
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), blockSound, blockParticle, GetActorLocation());
		cube->SetMaterial(0, blockMaterial);
		FVector curLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z+100);
		pointsWidget = GetWorld()->SpawnActor<APoints>(pointsWidgetClass, curLocation, GetActorRotation());
		if (pointsWidget!=nullptr)
		{
			pointsWidget->SetPoints(points);
		}
		coin = GetWorld()->SpawnActor<ACoinBlock>(coinClass, GetActorLocation(), GetActorRotation());
		if (coin != nullptr)
		{
			coin->UpdateCoins();
		}
		
		bIsBlock = true;
		if (platformerController != nullptr)
		{
			platformerController->UpdatePoints(points);
		}
		Tags.Remove("BlockP");
	}
}
