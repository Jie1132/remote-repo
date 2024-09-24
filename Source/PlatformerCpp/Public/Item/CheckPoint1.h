// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Components/TimelineComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/ArrowComponent.h"
#include "CheckPoint1.generated.h"

UCLASS()
class PLATFORMERCPP_API ACheckPoint1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DefaltSceneRoot")
	TObjectPtr<USceneComponent> defaultScenceRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box")
	TObjectPtr<UBoxComponent>box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagPivotPoint")
	TObjectPtr<UStaticMeshComponent> flagPivotPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagBase")
	TObjectPtr<UStaticMeshComponent> flagBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagArm")
	TObjectPtr<UStaticMeshComponent> flagArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flag")
	TObjectPtr<UStaticMeshComponent> flag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ReSpawnTransform")
	TObjectPtr<UArrowComponent> reSpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> timeline;
	FOnTimelineFloat timelineCallback;
	FOnTimelineEvent timelineFinished;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineCurve")
	TObjectPtr<UCurveFloat> timelineCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SoundFlag")
	TObjectPtr<USoundBase> soundFlag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ParticleFlag")
	TObjectPtr<UParticleSystem> particleFlag;

	bool bIsrise;
public:
	UFUNCTION()
	void BoxBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineStart(float value);

	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineFinished();

	
};
