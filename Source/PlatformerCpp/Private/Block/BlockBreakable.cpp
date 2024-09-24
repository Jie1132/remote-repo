// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockBreakable.h"
#include <PlatformerFunctionLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>
#include <PlatformerCpp/PlatformerCppCharacter.h>



void ABlockBreakable::HitBlock_Implementation()
{
	if (bIsBlock==false)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		APlatformerController* platformerController = Cast<APlatformerController>(playerController);
		APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player->hitPoints>=2)
		{
			UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), blockBreakSound, blockParticle, GetActorLocation());
			bIsBlock = true;
			if (platformerController != nullptr)
			{
				platformerController->UpdatePoints(points);
			}
			
			cube->SetMaterial(0, blockMaterial);
			pointsWidget = GetWorld()->SpawnActor<APoints>(pointsWidgetClass, GetActorLocation(), GetActorRotation());
			pointsWidget->SetPoints(points);
			Destroy();
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), blockSound);
		}
		

	
	}
	
	
}
