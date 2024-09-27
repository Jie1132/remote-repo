// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FireBar.h"
#include "Components/InstancedStaticMeshComponent.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>

// Sets default values
AFireBar::AFireBar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	fireCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FireCollision"));
	
	fireBar = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FireBar"));
	
	RootComponent = fireBar;
	fireCollision->SetupAttachment(RootComponent);
	fireRotating = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("FireRotation"));
	fireRotating->RotationRate = FRotator(50.f,0, 0);
	hitValue = -1;
	launchVelocity = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void AFireBar::BeginPlay()
{
	Super::BeginPlay();
	fireCollision->OnComponentBeginOverlap.AddDynamic(this, &AFireBar::BarBeginOverlop);
}

// Called every frame
void AFireBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireBar::OnConstruction(const FTransform& Transform)
{

}

void AFireBar::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (fireBall)
	{
		UE_LOG(LogTemp, Warning, TEXT("aaa"));
		if (lenValue> fireBar->GetInstanceCount())
		{
			fireBar->SetStaticMesh(fireBall);
			for (int i = fireBar->GetInstanceCount(); i < lenValue; i++)
			{
				FVector location = FVector(0.f, 0.f, flame * i);
				FTransform InstanceTransformer;
				InstanceTransformer.SetLocation(location);
				fireBar->AddInstance(InstanceTransformer);
			}
		}
		if (lenValue< fireBar->GetInstanceCount())
		{
			for (int i = fireBar->GetInstanceCount()-1; i >= lenValue; i--)
			{
				fireBar->RemoveInstance(i);
			}
		}
	}
	fireCollision->SetRelativeLocation(FVector(0.f, 0.f, (flame * (fireBar->GetInstanceCount()-1)) / 2));
	fireCollision->SetBoxExtent(FVector(50.0f, 50.0f, (flame * fireBar->GetInstanceCount()) / 2));

}

void AFireBar::BarBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr)
	{
		player->AdjustHitPoint(hitValue);
		player->LaunchCharacter(launchVelocity, true, true);
	}
}

