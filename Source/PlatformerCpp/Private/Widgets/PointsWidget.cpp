// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PointsWidget.h"
#include "Animation/WidgetAnimation.h"




void UPointsWidget::NativeConstruct()
{
	//Super::NativeConstruct();
	timelineAnim = NewObject<UTimelineComponent>(this, TEXT("Timeline"));
	timelineAnim->RegisterComponentWithWorld(GetWorld());
	timelineCallback.BindUFunction(this, FName("TimelineStart"));
	timelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));
	timelineAnim->AddInterpFloat(curveAnim,timelineCallback);
	timelineAnim->SetLooping(false);
	timelineAnim->PlayFromStart();
	timelineAnim->SetTimelineFinishedFunc(timelineFinishedCallback);
	startScale = FVector2D(0, 0);
	endScale = FVector2D(1, 1);
}

void UPointsWidget::SetPoints(int value)
{
	FText curPoints = FText::AsNumber(value);
	points->SetText(curPoints);
	/*Points_Animation = FindObject<UWidgetAnimation>(this, TEXT("Points_Animation"));
	if (Points_Animation != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Points_Animation"));
		PlayAnimation(Points_Animation);
	}*/
}

void UPointsWidget::TimelineStart(float value)
{
	FVector2D curScale = FMath::Lerp(startScale, endScale, value);
	points->SetRenderScale(curScale);
}

void UPointsWidget::TimelineFinished()
{
	//aPoints->Destroy();
	
}
