// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/PBlock.h"
#include "Kismet/GameplayStatics.h"
#include <Block/BlockBase.h>
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include <PlatformerFunctionLibrary.h>


// Sets default values
APBlock::APBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = defaultSceneRoot;
	
	blockP = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockP"));
	blockP->SetupAttachment(RootComponent);
	blockP->SetRelativeRotation(FRotator(0, 0, 90));

	box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box1"));
	box1->SetupAttachment(RootComponent);

	blockPBaseSmashed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockPBaseSmashed"));
	blockPBaseSmashed->SetupAttachment(RootComponent);

	blockPTopSmashed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockPTopSmashed"));
	blockPTopSmashed->SetupAttachment(RootComponent);

	boxSmashed = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxSmashed"));
	boxSmashed->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APBlock::BeginPlay()
{
	Super::BeginPlay();
	/*box1->OnComponentBeginOverlap.AddDynamic(this, &APBlock::Box1BeginOverlop);*/
	box1->OnComponentHit.AddDynamic(this, &APBlock::Box1Hit);
}

// Called every frame
void APBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APBlock::Box1Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr&&Hit.ImpactNormal.Z<0)
	{
		UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), pSound, blockPParticle, GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APBlock::Box1Off, 5.0f, false);
		FName TagToFind = FName("BlockP");
		TArray<AActor*> FoundActors;

		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagToFind, FoundActors);
		

		for (int i = 0; i < FoundActors.Num(); i++)
		{
			ABlockBase* block = Cast<ABlockBase>(FoundActors[i]);
			block->PBlockOn();
		}
		blockPBaseSmashed->SetVisibility(true, false);
		blockPTopSmashed->SetVisibility(true, false);
		box1->DestroyComponent();
		blockP->DestroyComponent();
	}
	

}

void APBlock::Box1Off()
{
	FName TagToFind = FName("BlockP");
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagToFind, FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++)
	{
		ABlockBase* block = Cast<ABlockBase>(FoundActors[i]);
		block->PBlockOff();
	}
}


