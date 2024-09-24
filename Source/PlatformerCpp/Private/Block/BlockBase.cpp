// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockBase.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include <Controllers/PlatformerController.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = defaultSceneRoot;
	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	cube->SetupAttachment(RootComponent);
	coinChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coin"));
	coinChild->SetupAttachment(RootComponent);
	coinBox = CreateDefaultSubobject<USphereComponent>(TEXT("CoinBox"));
	coinBox->SetupAttachment(coinChild);
	bIsBlock = false;
	timelineCube = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineCube"));
	
}

void ABlockBase::TimelineStart(float value)
{
	
	float curZ = FMath::Lerp(0, 50, value);
	cube->SetRelativeLocation(FVector(0, 0, curZ));
}

void ABlockBase::TimelineFinished()
{
}

// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	cur = GetActorLocation().Z;
	cube->OnComponentHit.AddDynamic(this, &ABlockBase::OnHit);
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	APlatformerController* platformerController = Cast<APlatformerController>(playerController);

	timelineCallback.BindUFunction(this, FName("TimelineStart"));
	timelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));

	timelineCube->AddInterpFloat(curveCube, timelineCallback);
	timelineCube->SetLooping(false);
	timelineCube->SetTimelineFinishedFunc(timelineFinishedCallback);

	coinBox->OnComponentBeginOverlap.AddDynamic(this,&ABlockBase::CoinBoxBeginOverlop);
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockBase::HitBlock_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("HitBlock_Implementation"));
}

void ABlockBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (Hit.ImpactNormal.Z > 0)
	{
		timelineCube->PlayFromStart();
	}
	
	if (player!=nullptr&&Hit.ImpactNormal.Z>0)
	{
		HitBlock_Implementation();
	}
	
}

void ABlockBase::PBlockOn()
{
	cube->SetVisibility(false,false);
	cube->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	coinChild->SetVisibility(true, false);
}

void ABlockBase::PBlockOff()
{
	cube->SetVisibility(true, false);
	cube->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	coinChild->SetVisibility(false , false);
}

void ABlockBase::CoinBoxBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("ada"))
		Destroy();
	}
}

