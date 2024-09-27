// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include "Components/BillboardComponent.h"
#include <Components/TimelineComponent.h>
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include "EndOfLevelFlag.generated.h"


UCLASS()
class PLATFORMERCPP_API AEndOfLevelFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndOfLevelFlag();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DefaltSceneRoot")
	TObjectPtr<USceneComponent> defaultScenceRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TriggerVolume")
	TObjectPtr<UBoxComponent>triggerVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireworksArea")
	TObjectPtr<UBoxComponent>fireworksArea;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagPivotPoint")
	TObjectPtr<UStaticMeshComponent> flagPivotPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagBase")
	TObjectPtr<UStaticMeshComponent> flagBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagArm")
	TObjectPtr<UStaticMeshComponent> flagArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flag")
	TObjectPtr<UStaticMeshComponent> flag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagEndPoint")
	TObjectPtr< UBillboardComponent>flagEndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerStartPoint")
	TObjectPtr<UArrowComponent> playerStartPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerEndPoint")
	TObjectPtr<UArrowComponent> playerEndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerExplodePoint")
	TObjectPtr<UArrowComponent> playerExplodePoint;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerController")
	TObjectPtr<APlatformerController> playerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	TObjectPtr<APlatformerCppCharacter> player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineFlag")
	TObjectPtr<UTimelineComponent> timelineFlag;
	FOnTimelineFloat timelineCallbackFlag;
	FOnTimelineEvent timelineFinishedFlag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelineFlagCurve")
	TObjectPtr<UCurveFloat> timelineFlagCurve;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelinePlayer")
	TObjectPtr<UTimelineComponent> timelinePlayer;
	FOnTimelineFloat timelineCallbackPlayer;
	FOnTimelineEvent timelineFinishedPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TimelinePlayerCurve")
	TObjectPtr<UCurveFloat> timelinePlayerCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SoundFlag")
	TObjectPtr<USoundBase> soundFlag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ParticleFlag")
	TObjectPtr<UParticleSystem> particleFlag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagAnim")
	TObjectPtr<UAnimationAsset> flagAnim;

	FVector flagStartPoint;
	FVector fireworkLocale;
	int fireworkpoints;
	int fireworkShowSpecial;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TriggerVolumeBeginOnerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void LevelComplele();

	UFUNCTION()
	void FlagStart(float value);
	UFUNCTION()
	void FlagFinished();

	UFUNCTION()
	void PlayerStart(float value);
	UFUNCTION()
	void PlayerFinished();
};
