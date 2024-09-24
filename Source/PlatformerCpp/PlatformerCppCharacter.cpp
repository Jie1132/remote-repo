// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerCppCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include <Platformer/PlatformerJump.h>
#include "PlatformerCppGameMode.h"
#include <PlatformerFunctionLibrary.h>
#include <Block/BlockBase.h>


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APlatformerCppCharacter

APlatformerCppCharacter::APlatformerCppCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 1500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	timelineScale = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineScale"));
	timelineDown = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineDown"));
	timelineUp = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineUp"));
	timelineDie = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineDie"));

	fireBallArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FireBallArrow"));
	fireBallArrow->SetupAttachment(this->GetMesh());
	fireBallArrow->SetRelativeLocation(FVector(0, 40, 135));
	fireBallArrow->SetRelativeRotation(FRotator(-30, 90, 0));

	flagAttchPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("flagAttchPoint"));
	flagAttchPoint->SetupAttachment(RootComponent);
	flagAttchPoint->SetRelativeLocation(FVector(40, 0, -55));

	smallScale = FVector(0.65f, 0.65f, 0.65f);
	bigScale = FVector(1.3, 1.3, 1.3);
	bOnPlatformer = false;
	bOnWarpPipe = false;
	hitPoints = 1;
	bIsInvincible = false;
	bHasFireFlower = false;
	bIsBig = false;
	bCanFire = true;

	platformerController =Cast<APlatformerController>(UGameplayStatics::GetPlayerController(this,0));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void APlatformerCppCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	this->OnDestroyed.AddDynamic(this, &APlatformerCppCharacter::PlayerOnDestroy);
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlatformerCppCharacter::CharacterBeginOverlop);
	this->GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlatformerCppCharacter::CharacterEndOverlop);

	timelineCallback.BindUFunction(this, FName("ScaleTimelineStart"));
	timelineFinishCallback.BindUFunction(this, FName("ScaleTimelineFinished"));
	timelineScale->AddInterpFloat(curveScale, timelineCallback);
	timelineScale->SetLooping(false);
	timelineScale->SetTimelineFinishedFunc(timelineFinishCallback);
	/*this->GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlatformerCppCharacter::CharacterEndOverlop);*/

	TimelineCallbackDown.BindUFunction(this, FName("DownTimelineStart"));
	TimelineFinishedCallbackDown.BindUFunction(this, FName("DownTimelineFinished"));

	timelineDown->AddInterpFloat(timeLineCurveDown, TimelineCallbackDown);
	timelineDown->SetLooping(false);
	timelineDown->SetTimelineFinishedFunc(TimelineFinishedCallbackDown);

	TimelineCallbackUp.BindUFunction(this, FName("UpTimelineStart"));
	TimelineFinishedCallbackUp.BindUFunction(this, FName("UpTimelineFinished"));

	timelineUp->AddInterpFloat(timeLineCurveUp, TimelineCallbackUp);
	timelineUp->SetLooping(false);
	timelineUp->SetTimelineFinishedFunc(TimelineFinishedCallbackUp);

	TimelineCallbackDie.BindUFunction(this, FName("DieTimelineStart"));
	TimelineFinishedCallbackDie.BindUFunction(this, FName("DieTimelineFinished"));

	timelineDie->AddInterpFloat(timeLineCurveDie, TimelineCallbackDie);
	timelineDie->SetLooping(false);
	timelineDie->SetTimelineFinishedFunc(TimelineFinishedCallbackDie);



	startLocation = GetActorLocation();
}


void APlatformerCppCharacter::CharacterBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerJump* platformer = Cast<APlatformerJump>(OtherActor);
	if (platformer!=nullptr)
	{
		bOnPlatformer = true;
		curPlatformer = platformer;
	}
	AWarpPipe* pipe = Cast<AWarpPipe>(OtherActor);
	if (pipe!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pipe"));
		bOnWarpPipe = true;
		CurWarpPipe = pipe;
	}
}
void APlatformerCppCharacter::CharacterEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWarpPipe* pipe = Cast<AWarpPipe>(OtherActor);
	if (pipe != nullptr)
	{
		bOnWarpPipe = false;
	}
}

void APlatformerCppCharacter::AdjustHitPoint(int value)
{
	if (value>0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitPointUpSound);
		hitPoints += value;
		if (hitPoints>3)
		{
			hitPoints = 3;
		}
	}
	if (bIsInvincible)
	{
		return;
	}
	if (value < 0)
	{
		bIsInvincible = true;
		
		hitPoints += value;
		if (hitPoints>0)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), hitPointDownSound);
		}
		if (hitPoints==2)
		{
			bHasFireFlower = false;
		}
		if (hitPoints==1)
		{
			bHasFireFlower = false;
			bIsBig = false;
			timelineScale->ReverseFromEnd();
			this->GetCapsuleComponent()->SetCapsuleHalfHeight(96);
			this->GetCapsuleComponent()->SetCapsuleRadius(34);
		}
		if (hitPoints < 0)
		{
			hitPoints = 0;
		}
	}
	this->GetMesh()->SetMaterial(0, materials[hitPoints]);
	GetWorld()->GetTimerManager().SetTimer(collisionTimehandle, this, &APlatformerCppCharacter::RestoreCollision, 1.f, false);
	if (hitPoints == 0)
	{
		Die();
		
		
	}
	
}

void APlatformerCppCharacter::RestoreCollision()
{
	bIsInvincible = false;
}

void APlatformerCppCharacter::RestoreFire()
{
	bCanFire = true;
}

void APlatformerCppCharacter::GetFlowerPower()
{
	if (bIsBig==false)
	{
		timelineScale->PlayFromStart();
	}
	bHasFireFlower = true;
}

void APlatformerCppCharacter::ScaleTimelineStart(float scaleValue)
{
	FVector curScale = FMath::Lerp(smallScale, bigScale,scaleValue);
	this->GetCapsuleComponent()->SetRelativeScale3D(curScale);
	//this->GetCapsuleComponent()->SetCapsuleHalfHeight(120);
	//this->GetCapsuleComponent()->SetCapsuleRadius(40);
}

void APlatformerCppCharacter::ScaleTimelineFinished()
{
}

void APlatformerCppCharacter::DownTimelineStart(float value)
{
	FVector curVector = FMath::Lerp(CurWarpPipe->warpInPoint->GetComponentLocation(), CurWarpPipe->warpOutPoint->GetComponentLocation(), value);
	this->GetCapsuleComponent()->SetRelativeLocation(curVector);
}

void APlatformerCppCharacter::DownTimelineFinished()
{
}

void APlatformerCppCharacter::DieTimelineStart(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("Die"));
	float curFloat = FMath::Lerp(50, 500, value);
	FVector curVector = FVector(GetActorLocation().X, GetActorLocation().Y, curFloat);
	/*this->GetCapsuleComponent()->SetRelativeLocation(curVector);*/
	this->GetMesh()->SetRelativeLocation(curVector);
}

void APlatformerCppCharacter::DieTimelineFinished()
{
}

void APlatformerCppCharacter::UpTimelineStart(float value)
{
	/*float curZ = FMath::Lerp(GetActorLocation().Z, GetActorLocation().Z + 50, value);*/
	FVector curVector = FMath::Lerp(CurWarpPipe->targetPipe->warpInPoint->GetComponentLocation(), CurWarpPipe->targetPipe->warpOutPoint->GetComponentLocation(), value);
	this->GetCapsuleComponent()->SetRelativeLocation(curVector);
	/*float curZ = FMath::Lerp(CurWarpPipe->targetPipe->warpInPoint->GetComponentLocation().Z, CurWarpPipe->targetPipe->warpOutPoint->GetComponentLocation().Z, value);
	this->GetCapsuleComponent()->SetRelativeLocation(FVector(CurWarpPipe->targetPipe->warpInPoint->GetComponentLocation().X, CurWarpPipe->targetPipe->warpInPoint->GetComponentLocation().Y, curZ));*/
}


void APlatformerCppCharacter::UpTimelineFinished()
{
}

void APlatformerCppCharacter::PlayerOnDestroy(AActor* DestroyedActor)
{
	APlatformerCppGameMode* gameMode = Cast<APlatformerCppGameMode>(UGameplayStatics::GetGameMode(this));
	gameMode->ReSpawn();
}






//////////////////////////////////////////////////////////////////////////
// Input

void APlatformerCppCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlatformerCppCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlatformerCppCharacter::Look);
		//Downing
		EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Triggered, this, &APlatformerCppCharacter::Down);
		//Up
		EnhancedInputComponent->BindAction(UpAction, ETriggerEvent::Triggered, this, &APlatformerCppCharacter::Up);
		//Shoot
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlatformerCppCharacter::Shoot);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlatformerCppCharacter::Die()
{
	this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->DisableInput(UGameplayStatics::GetPlayerController(this, 0));
	this->GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	timelineDie->PlayFromStart();
	UPlatformerFunctionLibrary::PlayBlockInteractFX(GetWorld(), platformerController->dieSound, platformerController->diePartic, GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, FTimerDelegate::CreateLambda([this]() {this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	this->EnableInput(UGameplayStatics::GetPlayerController(this, 0)); Destroy(); }), 1.f, false);	FName TagToFind = FName("BlockP");
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagToFind, FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++)
	{
		ABlockBase* block = Cast<ABlockBase>(FoundActors[i]);
		block->PBlockOff();
	}
}

void APlatformerCppCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, 0, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		
		AddMovementInput(ForwardDirection, MovementVector.X);
	}
}

void APlatformerCppCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlatformerCppCharacter::Down(const FInputActionValue& Value)
{
	if (bOnPlatformer)
	{
		curPlatformer->platFormer->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (bOnWarpPipe&&CurWarpPipe->bIsInteract&& CurWarpPipe->bIsDown)
	{
		
		this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->DisableInput(UGameplayStatics::GetPlayerController(this, 0));
		UGameplayStatics::PlaySound2D(this, CurWarpPipe->warpSound);

		timelineDown->PlayFromStart();

		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, FTimerDelegate::CreateLambda([this]() {
			
			this->GetCapsuleComponent()->SetRelativeLocation(CurWarpPipe->targetPipe->warpOutPoint->GetComponentLocation());
			UGameplayStatics::PlaySound2D(this, CurWarpPipe->warpSound);
			
			timelineUp->PlayFromStart();

			
			GetWorld()->GetTimerManager().SetTimer(TimerHandle2, FTimerDelegate::CreateLambda([this]() {
				
				this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				
				this->EnableInput(UGameplayStatics::GetPlayerController(this, 0));
				}), 1.f, false);

			}), 1.f, false);
	}
}

void APlatformerCppCharacter::Up(const FInputActionValue& Value)
{

	if (bOnWarpPipe && CurWarpPipe->bIsInteract && !CurWarpPipe->bIsDown)
	{
		this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->DisableInput(UGameplayStatics::GetPlayerController(this, 0));
		UGameplayStatics::PlaySound2D(this, CurWarpPipe->warpSound);
		// 播放 timelineDown 动画
		timelineDown->PlayFromStart();

		// 第一个定时器：延时 1 秒后，将角色传送到目标位置
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, FTimerDelegate::CreateLambda([this]() {
			// 设置位置
			this->GetCapsuleComponent()->SetRelativeLocation(CurWarpPipe->targetPipe->warpOutPoint->GetComponentLocation());
			UGameplayStatics::PlaySound2D(this, CurWarpPipe->warpSound);
			// 播放 timelineUp 动画
			timelineUp->PlayFromStart();

			// 第二个定时器：延时 1 秒后恢复碰撞并启用输入
			GetWorld()->GetTimerManager().SetTimer(TimerHandle2, FTimerDelegate::CreateLambda([this]() {
				// 恢复碰撞
				this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				// 重新启用输入
				this->EnableInput(UGameplayStatics::GetPlayerController(this, 0));
				}), 1.f, false);

			}), 1.f, false);
	}

}

void APlatformerCppCharacter::Shoot(const FInputActionValue& Value)
{
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),fireBallClass, outActors);
	if (bHasFireFlower && bCanFire && outActors.Num()<2)
	{
		fireBall = GetWorld()->SpawnActor<AFireBall>(fireBallClass, fireBallArrow->GetComponentLocation(), fireBallArrow->GetComponentRotation());
		bCanFire = false;
		UGameplayStatics::PlaySound2D(GetWorld(), ShootSound);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlatformerCppCharacter::RestoreFire, 0.15f, false);
	}
	
}
