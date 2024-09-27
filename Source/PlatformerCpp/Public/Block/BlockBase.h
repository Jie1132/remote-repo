// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "BPIPlatformer.h"
#include "Sound/SoundBase.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "BlockBase.generated.h"

UCLASS()
class PLATFORMERCPP_API ABlockBase : public AActor,public IBPIPlatformer
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefaultSceneRoot")
	TObjectPtr<USceneComponent>defaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cube")
	TObjectPtr<UStaticMeshComponent>cube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinChild")
	TObjectPtr<UChildActorComponent>coinChild;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinBox")
	TObjectPtr<USphereComponent>coinBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlockSound")
	TObjectPtr<USoundBase> blockSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlockBreakSound")
	TObjectPtr<USoundBase> blockBreakSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "blockParticle")
	TObjectPtr<UParticleSystem> blockParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "blockMaterial")
	TObjectPtr<UMaterial> blockMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> timelineCube;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Curve")
	TObjectPtr<UCurveFloat> curveCube;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins")
	int coins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
	int points;
	float cur;
	bool bIsBlock;
	FOnTimelineFloat timelineCallback;
	FOnTimelineEvent timelineFinishedCallback;

	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineFinished();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Í¨¹ý IBPIPlatformer ¼Ì³Ð
	void HitBlock_Implementation() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void PBlockOn();
	UFUNCTION()
	void PBlockOff();
	UFUNCTION()
	void CoinBoxBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
