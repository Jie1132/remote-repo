// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Flower.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>

// Sets default values
AFlower::AFlower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	flower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flower"));


	flowerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FlowerCollision"));
	RootComponent = flowerCollision;
	flower->SetupAttachment(RootComponent);
	flower->SetRelativeRotation(FRotator(0, 0, 90.f));


	hitValue = 2;
}

// Called when the game starts or when spawned
void AFlower::BeginPlay()
{
	Super::BeginPlay();
	flowerCollision->OnComponentBeginOverlap.AddDynamic(this, &AFlower::FlowerBeginOverlap);
}

// Called every frame
void AFlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlower::FlowerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast< APlatformerCppCharacter>(OtherActor);
	if (player != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("player"));
		player->GetFlowerPower();
		player->AdjustHitPoint(hitValue);
		Destroy();
	}
}

