// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Flower.h"
#include <Components/TimelineComponent.h>
#include "BlockFlower.generated.h"


/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API ABlockFlower : public AFlower
{
	GENERATED_BODY()
public:
	ABlockFlower();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineLocation")
	TObjectPtr<UTimelineComponent> timelineLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CurveLocation")
	TObjectPtr<UCurveFloat> curveLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineRotation")
	TObjectPtr<UTimelineComponent> timelineRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CurveRotation")
	TObjectPtr<UCurveFloat> curveRotation;
	
	FOnTimelineFloat locationCallback;
	FOnTimelineEvent locationFinishCallback;

	FOnTimelineFloat rotationCallback;
	FOnTimelineEvent rotationFinishCallback;

	FTimerHandle coinTimeHandle;

	UFUNCTION(BlueprintCallable, Category = "LocationTimeline")
	void LocationTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "LocationTimeline")
	void LocationTimelineFinished();

	UFUNCTION(BlueprintCallable, Category = "RotationTimeline")
	void RotationTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "RotationTimeline")
	void RotationTimelineFinished();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
