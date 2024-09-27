// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Goomba.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <PlatformerFunctionLibrary.h>

// Sets default values
AGoomba::AGoomba()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	collider->SetupAttachment(RootComponent);
	playerDetectRange = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectRange"));
	playerDetectRange->SetupAttachment(RootComponent);
	stompBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StompBox"));
	stompBox->SetupAttachment(collider);
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBook"));
	flipBook->SetupAttachment(collider);
	hitValue = -1;
	points = 200;
	speed = 200;
	bIsLeft = true;
	bmoveMent = false;
	bIsSeekEnemy = true;
	flipbookPlayRate = speed / 100;
}

// Called when the game starts or when spawned
void AGoomba::BeginPlay()
{
	Super::BeginPlay();
	collider->OnComponentBeginOverlap.AddDynamic(this, &AGoomba::ColliderBedginOverlop);
	collider->OnComponentHit.AddDynamic(this, &AGoomba::ColliderOnHit);
	stompBox->OnComponentHit.AddDynamic(this, &AGoomba::StompBoxOnHit);
	playerDetectRange->OnComponentBeginOverlap.AddDynamic(this, &AGoomba::DetectBedginOverlop);
	playerDetectRange->OnComponentEndOverlap.AddDynamic(this, &AGoomba::DetectEndOverlop);

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AGoomba::CylinderOnHit);
	bIsLeft = true;
	GetCharacterMovement()->MaxWalkSpeed = speed;
	
}

// Called every frame
void AGoomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bmoveMent)
	{
		APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!bIsSeekEnemy)
		{
			if (!bIsLeft)
			{
				this->AddMovementInput(FVector(1, 0, 0));
			}
			else
			{
				this->AddMovementInput(FVector(-1, 0, 0));
			}
		}
		else
		{
			if (player->GetActorLocation().X>this->GetActorLocation().X)
			{
				this->AddMovementInput(FVector(1, 0, 0));
			}
			else
			{
				this->AddMovementInput(FVector(-1, 0, 0));
			}
		}
	
		

	}
	
}

void AGoomba::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGoomba::ColliderBedginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr)
	{
		player->AdjustHitPoint(hitValue);
	}
}

void AGoomba::DetectBedginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (player!=nullptr)
	{
		bmoveMent = true;
	}
	
}
	


void AGoomba::DetectEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (player != nullptr)
	{
		bmoveMent = false;

	}
}



void AGoomba::ColliderOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AFireBall* fireball = Cast<AFireBall>(OtherActor);
	if (fireball != nullptr)
	{
		UpdataPoints();
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), fireSquish, particleGoomba, GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(timeHanndle, this, &AGoomba::DestroyGoomba, 0.05f, false);
	}
	
	
}

void AGoomba::StompBoxOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player != nullptr&&Hit.ImpactNormal.Z<0)
	{
		UpdataPoints();
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), squish, particleGoomba, GetActorLocation());
		this->SetActorScale3D(FVector(1, 1, 0.1));
		GetWorld()->GetTimerManager().SetTimer(timeHanndle, this, &AGoomba::DestroyGoomba, 0.2f, false);
		
	}
}



void AGoomba::CylinderOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.ImpactNormal.GetAbs().X > 0)
	{
		
		bIsLeft = !bIsLeft;
	}
}

void AGoomba::DestroyGoomba()
{
	Destroy();
}

void AGoomba::UpdataPoints()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	APlatformerController* platformerController = Cast<APlatformerController>(playerController);
	platformerController->UpdatePoints(points);
}

