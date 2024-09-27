// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include <Platformer/PlatformerJump.h>
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Components/TimelineComponent.h"
#include "Components/ArrowComponent.h"
#include "Item/FireBall.h"
#include <Pipe/WarpPipe.h>
#include <Controllers/PlatformerController.h>
#include "PlatformerCppCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APlatformerCppCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DownAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UpAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	

	

	
public:
	APlatformerCppCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlatformerController")
	TObjectPtr<APlatformerController> platformerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBallClass")
	TSubclassOf<AFireBall> fireBallClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBall")
	TObjectPtr<AFireBall> fireBall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "fireBallArrow")
	TObjectPtr<UArrowComponent> fireBallArrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagAttchPoint")
	TObjectPtr<UArrowComponent> flagAttchPoint;


	FTimerHandle collisionTimehandle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "curPlatformer")
	TObjectPtr<APlatformerJump> curPlatformer;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CurWarpPipe")
	TObjectPtr<AWarpPipe> CurWarpPipe;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	TArray<UMaterial*> materials;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "hitPointDownSound")
	TObjectPtr<USoundBase> hitPointDownSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "hitPointUpSound")
	TObjectPtr<USoundBase> hitPointUpSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ShootSound")
	TObjectPtr<USoundBase> ShootSound;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "hitPoints")
	int hitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> timelineScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurveScale")
	TObjectPtr<UCurveFloat> curveScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, CateGory = "TimelineDown")
	TObjectPtr<UTimelineComponent> timelineDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, CateGory = "TimelineUp")
	TObjectPtr<UTimelineComponent> timelineUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "timeLineCurveDown")
	TObjectPtr<UCurveFloat> timeLineCurveDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "timeLineCurveUp")
	TObjectPtr<UCurveFloat> timeLineCurveUp;

	FOnTimelineFloat TimelineCallbackDown;
	FOnTimelineEvent TimelineFinishedCallbackDown;

	FOnTimelineFloat TimelineCallbackUp;
	FOnTimelineEvent TimelineFinishedCallbackUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, CateGory = "TimelineDie")
	TObjectPtr<UTimelineComponent> timelineDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "timeLineCurveDown")
	TObjectPtr<UCurveFloat> timeLineCurveDie;

	FOnTimelineFloat TimelineCallbackDie;
	FOnTimelineEvent TimelineFinishedCallbackDie;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SmallScale")
	FVector smallScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bigScale")
	FVector bigScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StartLocation")
	FVector startLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bOnPlatformer")
	bool bOnPlatformer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bOnWarpPipe")
	bool bOnWarpPipe;
	
	FOnTimelineFloat timelineCallback;
	FOnTimelineEvent timelineFinishCallback;

	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	bool bIsInvincible;
	bool bHasFireFlower;
	bool bIsBig;
	bool bCanFire;
	

	UFUNCTION()
	void CharacterBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void CharacterEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void AdjustHitPoint(int value);

	UFUNCTION()
	void RestoreCollision();

	UFUNCTION()
	void RestoreFire();

	UFUNCTION()
	void GetFlowerPower();
	UFUNCTION(BlueprintCallable, Category = "ScaleTimelineStart")
	void ScaleTimelineStart(float scaleValue);
	UFUNCTION(BlueprintCallable, Category = "ScaleTimelineFinished")
	void ScaleTimelineFinished();

	UFUNCTION(BlueprintCallable, Category = "TimelineDown")
	void DownTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "TimelineDown")
	void DownTimelineFinished();

	UFUNCTION(BlueprintCallable, Category = "TimelineDie")
	void DieTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "TimelineDie")
	void DieTimelineFinished();

	UFUNCTION(BlueprintCallable, Category = "TimelineUp")
	void UpTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "TimelineUp")
	void UpTimelineFinished();

	UFUNCTION()
	void PlayerOnDestroy(AActor* DestroyedActor);

	UFUNCTION()
	void Die();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Down(const FInputActionValue& Value);

	void Up(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

