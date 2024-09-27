// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CoinBlock.h"
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>

// Sets default values
ACoinBlock::ACoinBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	timelineLocation = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineLocation"));
	timelineRotation = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineRocation"));
	cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));
	root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("root"));
	RootComponent = root;
	cylinder->SetupAttachment(RootComponent);
	cylinder->SetRelativeRotation(FRotator(-90.f, -20.f, -70.f));
	coinValue = 1;
	points = 100;
}

// Called when the game starts or when spawned
void ACoinBlock::BeginPlay()
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

// Called every frame
void ACoinBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoinBlock::LocationTimelineStart(float value)
{
	FVector curVector = FMath::Lerp(FVector(0,0,0), FVector(0, 0, 300), value);
	cylinder->SetRelativeLocation(curVector);
}

void ACoinBlock::LocationTimelineFinished()
{
}

void ACoinBlock::RotationTimelineStart(float value)
{
	FRotator curRotator = FMath::Lerp(FRotator(-90.f, -20.f, -70.f), FRotator(-90.f, 720, -70.f),value);
	cylinder->SetRelativeRotation(curRotator);
}

void ACoinBlock::RotationTimelineFinished()
{
}

void ACoinBlock::UpdateCoins()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	FVector location = GetActorLocation();
	APlatformerController* platformerController = Cast<APlatformerController>(playerController);
	platformerController->AddCoins(coinValue, location);
	platformerController->UpdatePoints(points);
	GetWorld()->GetTimerManager().SetTimer(coinTimeHandle, this, &ACoinBlock::DestroyCoin, 0.5f, false);
}

void ACoinBlock::DestroyCoin()
{
	Destroy();
}

