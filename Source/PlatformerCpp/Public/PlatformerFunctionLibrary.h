// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "PlatformerFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API UPlatformerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "PlayBlockInteractFX")
	static void PlayBlockInteractFX(UObject* wrold,USoundBase* sound,UParticleSystem* partic,FVector location);
};
