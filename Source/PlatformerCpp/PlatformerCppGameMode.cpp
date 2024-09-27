// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerCppGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>

APlatformerCppGameMode::APlatformerCppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APlatformerCppGameMode::BeginPlay()
{
	Super::BeginPlay();
	curPlayer = Cast<APlatformerCppCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void APlatformerCppGameMode::SetSpawnTransform(FTransform spawn)
{
	spawnTransforn = spawn;
}

void APlatformerCppGameMode::ReSpawn()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	APlatformerController* platformercontroller = Cast<APlatformerController>(playerController);
	FActorSpawnParameters SpawnParams;
	if (platformercontroller->lives > 0)
	{
		if (checkpoint)
		{
			FVector spawnLocation = checkpoint->reSpawnTransform->GetRelativeLocation();
			FRotator spawnRotation = checkpoint->reSpawnTransform->GetRelativeRotation();





			if (player != nullptr)
			{
				APlatformerCppCharacter* newPlayer = GetWorld()->SpawnActor<APlatformerCppCharacter>(player, spawnTransforn.GetLocation(), spawnRotation, SpawnParams);
				if (newPlayer)
				{
					newPlayer->GetCapsuleComponent()->SetWorldScale3D(newPlayer->smallScale);
					playerController->Possess(newPlayer);
					platformercontroller->UpdateLives(-1);
				}
			}

		}
		else
		{
			if (player != nullptr)
			{

				if (curPlayer)
				{
					APlatformerCppCharacter* newPlayer = GetWorld()->SpawnActor<APlatformerCppCharacter>(player, curPlayer->startLocation, FRotator(0, -90, 0), SpawnParams);
					if (newPlayer)
					{
						newPlayer->GetCapsuleComponent()->SetWorldScale3D(newPlayer->smallScale);
						playerController->Possess(newPlayer);
						platformercontroller->UpdateLives(-1);
					}
				}


			}
		}
	}
	
	
	
}
