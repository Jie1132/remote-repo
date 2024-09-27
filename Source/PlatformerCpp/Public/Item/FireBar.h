// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/StaticMeshComponent.h"

#include "FireBar.generated.h"

UCLASS()
class PLATFORMERCPP_API AFireBar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBar();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxCollision")
	TObjectPtr<UBoxComponent> fireCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBall")
	TObjectPtr<UStaticMesh> fireBall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBar")
	TObjectPtr<UInstancedStaticMeshComponent> fireBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireRotating")
	TObjectPtr<URotatingMovementComponent> fireRotating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Len")
	int lenValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitValue")
	int hitValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flame")
	float flame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaunchVelocity")
	FVector launchVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
	virtual void BarBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
