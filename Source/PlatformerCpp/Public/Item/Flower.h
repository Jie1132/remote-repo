// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Flower.generated.h"


UCLASS()
class PLATFORMERCPP_API AFlower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flower")
	TObjectPtr<UStaticMeshComponent> flower;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "FlowerCollision")
	TObjectPtr<UBoxComponent>flowerCollision;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Value")
	int hitValue;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void FlowerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
