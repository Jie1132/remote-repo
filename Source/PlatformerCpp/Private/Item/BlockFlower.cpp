// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BlockFlower.h"

ABlockFlower::ABlockFlower()
{
	PrimaryActorTick.bCanEverTick = true;
	timelineLocation = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineLocation"));
	timelineRotation = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineRocation"));

}

void ABlockFlower::LocationTimelineStart(float value)
{
	FVector curVector = FMath::Lerp(FVector(0, 0, 0), FVector(0, 0, 200), value);
	flower->SetRelativeLocation(curVector);
}

void ABlockFlower::LocationTimelineFinished()
{
}

void ABlockFlower::RotationTimelineStart(float value)
{
	FRotator curRotator = FMath::Lerp(FRotator(0.f, 0.f, 90.f), FRotator(0.f, 720, 90.f), value);
	flower->SetRelativeRotation(curRotator);
}

void ABlockFlower::RotationTimelineFinished()
{
}

void ABlockFlower::BeginPlay()
{
	Super::BeginPlay();
	locationCallback.BindUFunction(this, FName("LocationTimelineStart"));
	locationFinishCallback.BindUFunction(this, FName("LocationTimeStart"));
	timelineLocation->AddInterpFloat(curveLocation, locationCallback);
	timelineLocation->SetLooping(false);
	timelineLocation->SetTimelineFinishedFunc(locationFinishCallback);
	timelineLocation->PlayFromStart();

	rotationCallback.BindUFunction(this, FName("RotationTimelineStart"));
	rotationFinishCallback.BindUFunction(this, FName("RotationTimeStart"));
	timelineRotation->AddInterpFloat(curveRotation, rotationCallback);
	timelineRotation->SetLooping(false);
	timelineRotation->SetTimelineFinishedFunc(rotationFinishCallback);
	timelineRotation->PlayFromStart();
}
