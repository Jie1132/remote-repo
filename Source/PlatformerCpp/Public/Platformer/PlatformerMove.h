// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Platformer/PlatformerJump.h"
#include "Components/TimelineComponent.h"
#include "PlatformerMove.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API APlatformerMove : public APlatformerJump
{
	GENERATED_BODY()
public:
	APlatformerMove();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> timeline;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineCurve")
	TObjectPtr<UCurveFloat> timelineCurve;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	FVector startPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	FVector endPoint;

	FOnTimelineFloat TimelineCallback;
	FOnTimelineEvent TimelineFinishedCallback;

	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineFinished();
	virtual void BeginPlay() override;
};
