// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CheckPoint1.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include <PlatformerCpp/PlatformerCppGameMode.h>
#include <PlatformerCpp/PlatformerCppGameMode.h>
#include "Kismet/GameplayStatics.h"
#include <PlatformerFunctionLibrary.h>

// Sets default values
ACheckPoint1::ACheckPoint1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultScenceRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScenceRoot"));
	RootComponent = defaultScenceRoot;
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	box->SetupAttachment(RootComponent);
	box->SetBoxExtent(FVector(200, 200, 500));
	box->SetRelativeRotation(FRotator(0, 90, 0));
	flagPivotPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagPivotPoint"));
	flagPivotPoint->SetupAttachment(box);
	flagPivotPoint->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	flagPivotPoint->SetRelativeLocation(FVector(-200, 0, -400));
	flagBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("flagBase"));
	flagBase->SetupAttachment(box);
	flagBase->SetRelativeScale3D(FVector(0.5, 2, 2));
	flagBase->SetRelativeLocation(FVector(-200, 0, -500));
	flagArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagArm"));
	flagArm->SetupAttachment(box);
	flagArm->SetRelativeScale3D(FVector(0.5, 1, 1));
	flagArm->SetRelativeLocation(FVector(-205, 0, -390));
	flagArm->SetRelativeRotation(FRotator(0, 0, -90));
	flag=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
	flag->SetupAttachment(flagArm);
	flag->SetRelativeLocation(FVector(10, -10, 250));
	flag->SetRelativeScale3D(FVector(0.2, 1, 2));
	flag->SetRelativeRotation(FRotator(0, 0, -90));
	reSpawnTransform = CreateDefaultSubobject<UArrowComponent>(TEXT("ReSpawnTransform"));
	reSpawnTransform->SetupAttachment(box);
	reSpawnTransform->SetRelativeLocation(FVector(0, 0, -400));
	reSpawnTransform->SetRelativeRotation(FRotator(0, -90, 0));
	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	bIsrise = false;

}

// Called when the game starts or when spawned
void ACheckPoint1::BeginPlay()
{
	Super::BeginPlay();
	box->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint1::BoxBeginOverlop);
	timelineCallback.BindUFunction(this, FName("TimelineStart"));
	timelineFinished.BindUFunction(this, FName("TimelineFinish"));

	timeline->AddInterpFloat(timelineCurve, timelineCallback);
	timeline->SetLooping(false);
	timeline->SetTimelineFinishedFunc(timelineFinished);
}

// Called every frame
void ACheckPoint1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPoint1::BoxBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BoxBeginOverlop"));
		APlatformerCppGameMode* gameMode= Cast<APlatformerCppGameMode>(UGameplayStatics::GetGameMode(this));
		gameMode->SetSpawnTransform(reSpawnTransform->GetComponentTransform());
		gameMode->checkpoint = Cast<ACheckPoint1>(this);
		if (bIsrise==false)
		{
			timeline->PlayFromStart();
			UPlatformerFunctionLibrary::PlayBlockInteractFX(this, soundFlag, particleFlag,flagBase->GetComponentLocation());
			bIsrise = true;
		}
		
	}
}

void ACheckPoint1::TimelineStart(float value)
{
	FRotator curRotator = FMath::Lerp(FRotator(0, 0, -90), FRotator(0, 0, 0),value);
	flagArm->SetRelativeRotation(curRotator);
}

void ACheckPoint1::TimelineFinished()
{

}

