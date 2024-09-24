// Fill out your copyright notice in the Description page of Project Settings.


#include "Pipe/WarpPipe.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>


// Sets default values
AWarpPipe::AWarpPipe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultScenceRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScenceRoot"));
	RootComponent = defaultScenceRoot;
	pipeBody = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PipeBody"));
	pipeBody->SetupAttachment(RootComponent);
	pipeTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PipeTop"));
	pipeTop->SetupAttachment(RootComponent);
	pipeInside = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PipeInside"));
	pipeInside->SetupAttachment(pipeTop);
	collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	collision->SetupAttachment(pipeTop);
	warpInPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("WarpInPoint"));
	warpInPoint->SetupAttachment(RootComponent);
	warpOutPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("WarpOutPoint"));
	warpOutPoint->SetupAttachment(RootComponent);
	lenvalue = 1;
	flame = 100;
}

// Called when the game starts or when spawned
void AWarpPipe::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AWarpPipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWarpPipe::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	int pipeBodyCount = pipeBody->GetInstanceCount();
	for (int i = pipeBody->GetInstanceCount() - 1; i >= 0; i--)
	{
		pipeBody->RemoveInstance(i);
	}
	for (int i = 0; i < lenvalue; i++)
	{
		FVector location = FVector(0, 0, -flame * i);
		FTransform pipeTransform;
		pipeTransform.SetLocation(location);
		pipeBody->AddInstance(pipeTransform);
	}
}

void AWarpPipe::DownTimelineStart(float value)
{

}

void AWarpPipe::DownTimelineFinished()
{

}

void AWarpPipe::UpTimelineStart(float value)
{

}

void AWarpPipe::UpTimelineFinished()
{

}



