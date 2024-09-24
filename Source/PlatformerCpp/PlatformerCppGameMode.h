// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <Item/CheckPoint1.h>
#include "PlatformerCppCharacter.h"
#include "PlatformerCppGameMode.generated.h"


UCLASS(minimalapi)
class APlatformerCppGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlatformerCppGameMode();
	FTransform  spawnTransforn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	TSubclassOf<APlatformerCppCharacter> player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CurPlayer")
	TObjectPtr<APlatformerCppCharacter> curPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckPoint")
	TObjectPtr<ACheckPoint1> checkpoint;
	

public:
	virtual void BeginPlay();


	UFUNCTION()
	void SetSpawnTransform(FTransform spawn);

	UFUNCTION()
	void ReSpawn();
};



