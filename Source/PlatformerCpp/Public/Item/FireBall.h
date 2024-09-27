// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireBall.generated.h"

UCLASS()
class PLATFORMERCPP_API AFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBall();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBall")
	TObjectPtr<UStaticMeshComponent> fireBall;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBallParticle")
	TObjectPtr<UParticleSystemComponent> fireBallParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBallMovemnt")
	TObjectPtr<UProjectileMovementComponent> fireBallMovemnt;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBallEmitter")
	TObjectPtr<UParticleSystem> fireBallEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBallSound")
	TObjectPtr<USoundBase> fireBallSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BounceCounter")
	int bounceCounter;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BounceCount(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
};
