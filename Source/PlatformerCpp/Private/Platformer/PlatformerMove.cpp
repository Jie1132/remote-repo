// Fill out your copyright notice in the Description page of Project Settings.


#include "Platformer/PlatformerMove.h"

APlatformerMove::APlatformerMove()
{
	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}

void APlatformerMove::TimelineStart(float value)
{
	FVector location = FMath::Lerp(startPoint, endPoint, value);
	platFormer->SetRelativeLocation(location);
}

void APlatformerMove::TimelineFinished()
{

}

void APlatformerMove::BeginPlay()
{
	Super::BeginPlay();
	TimelineCallback.BindUFunction(this, FName("TimelineStart"));
	TimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));

	timeline->AddInterpFloat(timelineCurve, TimelineCallback);
	timeline->SetLooping(true);
	timeline->PlayFromStart();
	timeline->SetTimelineFinishedFunc(TimelineFinishedCallback);

}
