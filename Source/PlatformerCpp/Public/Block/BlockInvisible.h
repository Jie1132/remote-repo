// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block/BlocCoin.h"
#include "Components/BoxComponent.h"
#include "BlockInvisible.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API ABlockInvisible : public ABlocCoin
{
	GENERATED_BODY()
public:
	ABlockInvisible();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BoxCollision")
	TObjectPtr<UBoxComponent> boxCollision;

	virtual void BeginPlay() override;

	void HitBlock_Implementation() override;

	UFUNCTION()
	void BoxBeginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void BoxEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
