// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Coin.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include "Kismet/GameplayStatics.h"
#include <Controllers/PlatformerController.h>
// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	coin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin"));
	
	
	coinCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CoinCollision"));
	RootComponent = coinCollision;
	coin->SetupAttachment(RootComponent);
	coin->SetRelativeRotation(FRotator(-90.f, -20.f, -70.f));
	

	coinRotating = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("CoinRotating"));
	coinRotating->RotationRate = FRotator(0.f, 90.f, 0.f);
	value = 1;
	points = 100;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	coinCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::CoinBeginOverlap);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::CoinBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast< APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("player"));*/
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		APlatformerController* PlatformerController = Cast<APlatformerController>(PlayerController);
		if (PlatformerController!=nullptr)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("comtroller"));*/
			FVector location = GetActorLocation();
			PlatformerController->AddCoins(value, location);
			PlatformerController->UpdatePoints(points);
			Destroy();
		}
	}
}

