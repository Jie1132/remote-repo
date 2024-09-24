// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPlatformerFunctionLibrary::PlayBlockInteractFX(UObject* wrold,USoundBase* sound, UParticleSystem* partic, FVector location)
{
	UGameplayStatics::PlaySound2D(wrold, sound);
	UGameplayStatics::SpawnEmitterAtLocation(wrold,partic, location);
}
