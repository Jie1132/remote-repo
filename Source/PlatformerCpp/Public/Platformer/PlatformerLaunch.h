// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Components/TimelineComponent.h"
#include "PlatformerLaunch.generated.h"

UCLASS()
class PLATFORMERCPP_API APlatformerLaunch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerLaunch();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MushroomTop")
	TObjectPtr<UStaticMeshComponent> mushroomTop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "instancedMushroomTrunk")
	TObjectPtr<UInstancedStaticMeshComponent> instancedMushroomTrunk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MushroomTrunk")
	TObjectPtr<UStaticMesh> mushroomTrunk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopCollision")
	TObjectPtr<UBoxComponent> topCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaunchSound")
	TObjectPtr<USoundBase> launchSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaunchPartic")
	TObjectPtr<UParticleSystem> launchPartic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine")
	TObjectPtr<UTimelineComponent> timeLine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "timeLineCurve")
	TObjectPtr<UCurveFloat> timeLineCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LenValue")
	int lenValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flame")
	float flame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flame")
	FVector launchVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flame")
	FVector startScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flame")
	FVector endScale;

	FOnTimelineFloat TimelineCallback;
	FOnTimelineEvent TimelineFinishedCallback;

	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineFinished();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
	virtual void TopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
