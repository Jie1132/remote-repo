// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockInvisible.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Controllers/PlatformerController.h>
#include "Engine/EngineTypes.h"
#include <PlatformerFunctionLibrary.h>

ABlockInvisible::ABlockInvisible()
{
	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->SetupAttachment(cube);
}

void ABlockInvisible::BeginPlay()
{
	Super::BeginPlay();
	boxCollision->OnComponentBeginOverlap.AddDynamic(this,&ABlockInvisible::BoxBeginOverlop);
	boxCollision->OnComponentEndOverlap.AddDynamic(this, &ABlockInvisible::BoxEndOverlop);
	cube->SetVisibility(false,true);
	cube->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1,ECR_Ignore);
	coinChild->DestroyChildActor();
	coinBox->DestroyComponent();
}

void ABlockInvisible::HitBlock_Implementation()
{
	if (bIsBlock == false)
	{
		cube->SetVisibility(true, true);
		cube->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Block);
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		APlatformerController* platformerController = Cast<APlatformerController>(playerController);
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), blockSound, blockParticle, GetActorLocation());
		cube->SetMaterial(0, blockMaterial);
		FVector curLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100);
		pointsWidget = GetWorld()->SpawnActor<APoints>(pointsWidgetClass, curLocation, GetActorRotation());
		if (pointsWidget != nullptr)
		{
			pointsWidget->SetPoints(points);
		}
		coin = GetWorld()->SpawnActor<ACoinBlock>(coinClass, GetActorLocation(), GetActorRotation());
		if (coin != nullptr)
		{
			coin->UpdateCoins();
		}

		bIsBlock = true;
		if (platformerController != nullptr)
		{
			platformerController->UpdatePoints(points);
		}
	}
}

void ABlockInvisible::BoxBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player&&bIsBlock==false)
	{
		cube->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABlockInvisible::BoxEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player && bIsBlock == false)
	{
		cube->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
