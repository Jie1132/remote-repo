// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Components/TimelineComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "WarpPipe.generated.h"

UCLASS()
class PLATFORMERCPP_API AWarpPipe : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarpPipe();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DefaultScenceRoot")
	TObjectPtr<USceneComponent> defaultScenceRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WarpSound")
	TObjectPtr<USoundBase> warpSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PipeTop")
	TObjectPtr<UStaticMeshComponent>pipeTop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PipeBody")
	TObjectPtr<UInstancedStaticMeshComponent>pipeBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PipeInside")
	TObjectPtr<UStaticMeshComponent>pipeInside;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<UCapsuleComponent>collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WarpInPoint")
	TObjectPtr< UBillboardComponent>warpInPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WarpOutPoint")
	TObjectPtr< UBillboardComponent>warpOutPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TargetPipe")
	TObjectPtr< AWarpPipe>targetPipe;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LenValue")
	int lenvalue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flame")
	float flame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bIsInteract")
	bool bIsInteract;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bIsDown")
	bool bIsDown;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION(BlueprintCallable, Category = "TimelineDown")
	void DownTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "TimelineDown")
	void DownTimelineFinished();

	UFUNCTION(BlueprintCallable, Category = "TimelineUp")
	void UpTimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "TimelineUp")
	void UpTimelineFinished();
};
