// Fill out your copyright notice in the Description page of Project Settings.


#include "Platformer/PlatformerJump.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>

// Sets default values
APlatformerJump::APlatformerJump()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	platFormer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("platFormer"));
	RootComponent = platFormer;
	bottomCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("bottomCollision"));
	bottomCollision->SetupAttachment(RootComponent);

	topCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("topCollision"));
	topCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlatformerJump::BeginPlay()
{
	Super::BeginPlay();
	bottomCollision->OnComponentBeginOverlap.AddDynamic(this,&APlatformerJump::BottomBeginOverlop);
	bottomCollision->OnComponentEndOverlap.AddDynamic(this, &APlatformerJump::BottomEndOverlop);
	topCollision->OnComponentBeginOverlap.AddDynamic(this, &APlatformerJump::TopBeginOverlop);
	topCollision->OnComponentEndOverlap.AddDynamic(this, &APlatformerJump::TopmEndOverlop);
}

// Called every frame
void APlatformerJump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformerJump::BottomBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr)
	{
		platFormer->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APlatformerJump::BottomEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player != nullptr)
	{
		platFormer->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void APlatformerJump::TopBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player != nullptr)
	{
		player->bOnPlatformer = true;
	}
}

void APlatformerJump::TopmEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player != nullptr)
	{
		player->bOnPlatformer = false;
	}
}



