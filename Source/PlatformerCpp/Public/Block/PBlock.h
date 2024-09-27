// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "PBlock.generated.h"

UCLASS()
class PLATFORMERCPP_API APBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APBlock();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefaultSceneRoot")
	TObjectPtr<USceneComponent>defaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlockP")
	TObjectPtr<UStaticMeshComponent> blockP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box1")
	TObjectPtr<UBoxComponent> box1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlockPBaseSmashed")
	TObjectPtr<UStaticMeshComponent> blockPBaseSmashed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlockPTopSmashed")
	TObjectPtr<UStaticMeshComponent> blockPTopSmashed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BoxSmashed")
	TObjectPtr<UBoxComponent> boxSmashed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PSound")
	TObjectPtr<USoundBase> pSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlockPParticle")
	TObjectPtr<UParticleSystem> blockPParticle;


	FTimerHandle TimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Box1Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void Box1Off();
};
