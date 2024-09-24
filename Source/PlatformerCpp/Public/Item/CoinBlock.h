// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CoinBlock.generated.h"

UCLASS()
class PLATFORMERCPP_API ACoinBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinBlock();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineLocation")
	TObjectPtr<UTimelineComponent> timelineLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CurveLocation")
	TObjectPtr<UCurveFloat> curveLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineRotation")
	TObjectPtr<UTimelineComponent> timelineRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CurveRotation")
	TObjectPtr<UCurveFloat> curveRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "root")
	TObjectPtr<UStaticMeshComponent> root;

	int coinValue;

	int points;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cylinder")
	TObjectPtr<UStaticMeshComponent> cylinder;
	FOnTimelineFloat locationCallback;
	FOnTimelineEvent locationFinishCallback;

	FOnTimelineFloat rotationCallback;
	FOnTimelineEvent rotationFinishCallback;

	FTimerHandle coinTimeHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LocationTimeline")
	void LocationTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "LocationTimeline")
	void LocationTimelineFinished();

	UFUNCTION(BlueprintCallable, Category = "RotationTimeline")
	void RotationTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "RotationTimeline")
	void RotationTimelineFinished();

	UFUNCTION()
	void UpdateCoins();
	UFUNCTION()
	void DestroyCoin();
};
