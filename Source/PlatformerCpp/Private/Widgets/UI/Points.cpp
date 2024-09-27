// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UI/Points.h"
#include <Widgets/PointsWidget.h>
#include "Kismet/GameplayStatics.h"
#include <Controllers/PlatformerController.h>

// Sets default values
APoints::APoints()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pointsWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PointsWidget"));
	RootComponent = pointsWidget;
}

// Called when the game starts or when spawned
void APoints::BeginPlay()
{
	Super::BeginPlay();
	
	/*widget->NativeConstruct();*/
	//APlayerController* pl = UGameplayStatics::GetPlayerController(this,0);
	//APlatformerController* player = Cast<APlatformerController>(pl);
	//player->UpdatePoints(pointsToAdd);
	
}

// Called every frame
void APoints::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoints::SetPoints(int value)
{
	UPointsWidget* widget = Cast<UPointsWidget>(pointsWidget->GetWidget());
	widget->SetPoints(value);
	GetWorld()->GetTimerManager().SetTimer(breakTimehandle, this, &APoints::Destroy1, 1.f, false);
}

void APoints::Destroy1()
{
	Destroy();
}



