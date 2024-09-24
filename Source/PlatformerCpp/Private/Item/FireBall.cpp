// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FireBall.h"
#include "Kismet/GameplayStatics.h"
#include <PlatformerFunctionLibrary.h>

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	fireBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireBall"));
	/*fireBall->SetupAttachment(RootComponent);*/
	RootComponent = fireBall;
	fireBallParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireBallParticle"));
	fireBallParticle->SetupAttachment(RootComponent);

	fireBallMovemnt = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("FireBallMovement"));
	fireBallMovemnt->InitialSpeed = 1000;
	fireBallMovemnt->MaxSpeed = 1000;
	fireBallMovemnt->bShouldBounce = true;
	fireBallMovemnt->Bounciness = 0.5;
	fireBallMovemnt->Friction = 0;
	this->InitialLifeSpan = 2;

	bounceCounter = 0;
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	fireBallMovemnt->OnProjectileBounce.AddDynamic(this, &AFireBall::BounceCount);
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireBall::BounceCount(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	bounceCounter++;
	if (bounceCounter>=2)
	{
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), fireBallSound, fireBallEmitter, GetActorLocation());
		Destroy();
	}
	if (ImpactResult.Normal.GetAbs().Z<0.9)
	{
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), fireBallSound, fireBallEmitter, GetActorLocation());
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireBallEmitter, GetActorLocation(), GetActorRotation(), FVector(1.0f));
		//UGameplayStatics::PlaySound2D(GetWorld(), fireBallSound);
		Destroy();
	}
}

