// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Coin.generated.h"



UCLASS()
class PLATFORMERCPP_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	TObjectPtr<UStaticMeshComponent> coin;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "CoinCollision")
	TObjectPtr<UBoxComponent>coinCollision;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "CoinRotating")
	TObjectPtr<URotatingMovementComponent> coinRotating;




	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Value")
	int value;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Points")
	int points;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CoinBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
