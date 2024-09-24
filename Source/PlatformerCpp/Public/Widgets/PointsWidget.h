// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/EditableText.h"
#include "Components/Overlay.h"
#include "Components/TimelineComponent.h"
#include "PointsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERCPP_API UPointsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> points;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
	TObjectPtr<UOverlay> overlay;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (BindWidgetAnim))
	//UWidgetAnimation* Points_Animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pointsValue")
	int pointsValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimelineAnim")
	TObjectPtr<UTimelineComponent> timelineAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurveAnim")
	TObjectPtr<UCurveFloat> curveAnim;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurveAnim")
	//TObjectPtr<APoints> aPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	FVector2D startScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timeline")
	FVector2D endScale;

	FOnTimelineFloat timelineCallback;
	FOnTimelineEvent timelineFinishedCallback;
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetPoints(int value);

	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineStart(float value);
	UFUNCTION(BlueprintCallable, Category = "Timeline")
	void TimelineFinished();
};
