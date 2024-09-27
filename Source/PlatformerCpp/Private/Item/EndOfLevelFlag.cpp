// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EndOfLevelFlag.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <PlatformerFunctionLibrary.h>
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AEndOfLevelFlag::AEndOfLevelFlag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultScenceRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScenceRoot"));
	RootComponent = defaultScenceRoot;
	triggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	triggerVolume->SetupAttachment(RootComponent);
	triggerVolume->SetRelativeLocation(FVector(10, 0, 1000));
	triggerVolume->SetBoxExtent(FVector(32, 200, 1000));
	triggerVolume->SetRelativeRotation(FRotator(0, 0, 0));

	fireworksArea = CreateDefaultSubobject<UBoxComponent>(TEXT("FireworksArea"));
	fireworksArea->SetupAttachment(RootComponent);
	fireworksArea->SetBoxExtent(FVector(200, 500, 300));
	fireworksArea->SetRelativeRotation(FRotator(0, 90, 0));
	fireworksArea->SetRelativeLocation(FVector(850, 0, 700));
	fireworksArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	flagPivotPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagPivotPoint"));
	flagPivotPoint->SetupAttachment(RootComponent);
	flagPivotPoint->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	flagPivotPoint->SetRelativeLocation(FVector(0, 0, 895));
	flagBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("flagBase"));
	flagBase->SetupAttachment(RootComponent);
	flagBase->SetRelativeScale3D(FVector(1, 1, 1));
	flagBase->SetRelativeLocation(FVector(0, 0, 50));
	flagArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagArm"));
	flagArm->SetupAttachment(RootComponent);
	flagArm->SetRelativeScale3D(FVector(0.2, 0.2, 8));
	flagArm->SetRelativeLocation(FVector(0, 0, 500));
	flagArm->SetRelativeRotation(FRotator(0, 0,0));
	flag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
	flag->SetupAttachment(RootComponent);
	flag->SetRelativeLocation(FVector(85,0, 845));
	flag->SetRelativeScale3D(FVector(1.5, 1, 1));
	flag->SetRelativeRotation(FRotator(0, 0, 90));

	flagEndPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("FlagEndPoint"));
	flagEndPoint->SetupAttachment(RootComponent);
	flagEndPoint->SetRelativeLocation(FVector(0, 0, 150));
	flagEndPoint->SetRelativeRotation(FRotator(0, 0, 90));

	playerStartPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerStartPoint"));
	playerStartPoint->SetupAttachment(RootComponent);
	playerStartPoint->SetRelativeLocation(FVector(-25, 30, 845));
	playerStartPoint->SetRelativeRotation(FRotator(0, 0, 0));

	playerEndPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerEndPoint"));
	playerEndPoint->SetupAttachment(RootComponent);
	playerEndPoint->SetRelativeLocation(FVector(-25, 30, 110));
	playerEndPoint->SetRelativeRotation(FRotator(0, 0, 0));

	playerExplodePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerExplodePoint"));
	playerExplodePoint->SetupAttachment(RootComponent);
	playerExplodePoint->SetRelativeLocation(FVector(850, 0, 500));
	playerExplodePoint->SetRelativeRotation(FRotator(0, 0, 0));
	timelineFlag = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineFlag"));
	timelinePlayer= CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelinePlayer"));
	

	flagStartPoint = FVector(0, 0, 0);
	fireworkLocale = FVector(0, 0, 0);
	fireworkpoints = 500;
	fireworkShowSpecial = 7;
}

// Called when the game starts or when spawned
void AEndOfLevelFlag::BeginPlay()
{
	Super::BeginPlay();
	playerController = Cast<APlatformerController>(UGameplayStatics::GetPlayerController(this, 0));
	triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AEndOfLevelFlag::TriggerVolumeBeginOnerlap);

	timelineCallbackFlag.BindUFunction(this, FName("FlagStart"));
	timelineFinishedFlag.BindUFunction(this, FName("FlagFinished"));
	timelineFlag->AddInterpFloat(timelineFlagCurve, timelineCallbackFlag);
	timelineFlag->SetLooping(false);
	timelineFlag->SetTimelineFinishedFunc(timelineFinishedFlag);

	timelineCallbackPlayer.BindUFunction(this, FName("PlayerStart"));
	timelineFinishedPlayer.BindUFunction(this, FName("PlayerFinished"));
	timelinePlayer->AddInterpFloat(timelinePlayerCurve, timelineCallbackPlayer);
	timelinePlayer->SetLooping(false);
	timelinePlayer->SetTimelineFinishedFunc(timelineFinishedPlayer);
}

// Called every frame
void AEndOfLevelFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndOfLevelFlag::TriggerVolumeBeginOnerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player)
	{
		player->DisableInput(playerController);
		LevelComplele ();
	}
}

void AEndOfLevelFlag::LevelComplele()
{
	FVector startLocation=player->flagAttchPoint->GetComponentLocation();
	UCharacterMovementComponent* MovementComponent = player->GetCharacterMovement();
	MovementComponent->GravityScale = 0;
	MovementComponent->Deactivate();

	player->GetMesh()->PlayAnimation(flagAnim,false);
	player->GetMesh()->SetPosition(1.25f,true);
	
	if (startLocation.Z> flag->GetComponentLocation().Z)
	{
		flagStartPoint = flag->GetComponentLocation();
		player->GetCapsuleComponent()->SetWorldLocation(playerStartPoint->GetComponentLocation());
	}
	else
	{
		flagStartPoint =FVector(flag->GetComponentLocation().X, flag->GetComponentLocation().Y,startLocation.Z);
		player->GetCapsuleComponent()->AddLocalOffset(FVector(30, 0, 0));
	}
	flag->SetWorldLocation(flagStartPoint);
	UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), soundFlag, particleFlag, GetActorLocation());
	timelineFlag->PlayFromStart();
	timelinePlayer->PlayFromStart();
}

void AEndOfLevelFlag::FlagStart(float value)
{
	

	FVector location = FMath::Lerp(flagStartPoint, flagEndPoint->GetComponentTransform().GetLocation(), value);
	flag->SetWorldLocation(location);
}

void AEndOfLevelFlag::FlagFinished()
{
}

void AEndOfLevelFlag::PlayerStart(float value)
{
	FVector startLocation = player->flagAttchPoint->GetComponentLocation();
	FVector location = FMath::Lerp(startLocation, playerEndPoint->GetComponentLocation(), value);
	player->GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));
	player->GetMesh()->SetWorldLocation(location);
	player->GetCameraBoom()->SetWorldLocation(location);
	
}

void AEndOfLevelFlag::PlayerFinished()
{
}

