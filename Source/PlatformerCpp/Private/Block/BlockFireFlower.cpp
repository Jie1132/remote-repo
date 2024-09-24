// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockFireFlower.h"
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>
#include <PlatformerFunctionLibrary.h>

void ABlockFireFlower::HitBlock_Implementation()
{
	if (bIsBlock == false)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		APlatformerController* platformerController = Cast<APlatformerController>(playerController);
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), blockSound, blockParticle, GetActorLocation());
		cube->SetMaterial(0, blockMaterial);
		FVector curLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100);
		pointsWidget = GetWorld()->SpawnActor<APoints>(pointsWidgetClass, curLocation, GetActorRotation());
		if (pointsWidget != nullptr)
		{
			pointsWidget->SetPoints(points);
		}
		FVector flowerLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 80);
		flower = GetWorld()->SpawnActor<ABlockFlower>(flowerClass, flowerLocation, GetActorRotation());
		bIsBlock = true;
		if (platformerController != nullptr)
		{
			platformerController->UpdatePoints(points);
		}
	}
}
