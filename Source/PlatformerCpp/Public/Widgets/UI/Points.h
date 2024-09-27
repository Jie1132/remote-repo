// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
#include "Widgets/PointsWidget.h"
#include "Points.generated.h"


UCLASS()
class PLATFORMERCPP_API APoints : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoints();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsWidget")
	TObjectPtr<UWidgetComponent> pointsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsToAdd")
	int pointsToAdd;

	FTimerHandle breakTimehandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetPoints(int value);

	UFUNCTION()
	void Destroy1();


};
