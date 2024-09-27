// Fill out your copyright notice in the Description page of Project Settings.


#include "Platformer/PlatformerLaunch.h"
#include "Components/InstancedStaticMeshComponent.h"
#include <PlatformerCpp/PlatformerCppCharacter.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
APlatformerLaunch::APlatformerLaunch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mushroomTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MushroomTop"));
	RootComponent = mushroomTop;

	instancedMushroomTrunk = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMushroomTrunk"));
	instancedMushroomTrunk->SetupAttachment(RootComponent);

	topCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TopCollision"));
	topCollision->SetupAttachment(RootComponent);


	timeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	lenValue = 1;
	flame = 100;
	launchVelocity = FVector(0.f, 0.f, 1000.f);
	startScale = FVector(5.f, 5.f, 0.5f);
	endScale = FVector(6.f, 6.f, 0.5f);
}



// Called when the game starts or when spawned
void APlatformerLaunch::BeginPlay()
{
	Super::BeginPlay();
	topCollision->OnComponentBeginOverlap.AddDynamic(this, &APlatformerLaunch::TopBeginOverlap);

	TimelineCallback.BindUFunction(this, FName("TimelineStart"));
	TimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));

	timeLine->AddInterpFloat(timeLineCurve, TimelineCallback);
	timeLine->SetLooping(false);
	timeLine->SetTimelineFinishedFunc(TimelineFinishedCallback);
}

void APlatformerLaunch::TimelineStart(float value)
{
	FVector curScale = FMath::Lerp(startScale, endScale, value);
	mushroomTop->SetRelativeScale3D(curScale);
}

void APlatformerLaunch::TimelineFinished()
{
}
void APlatformerLaunch::OnConstruction(const FTransform& Transform)
{
	
}

void APlatformerLaunch::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// 处理属性更改逻辑
	if (mushroomTrunk)
	{
		int32 CurrentInstanceCount = instancedMushroomTrunk->GetInstanceCount();
		if (lenValue> instancedMushroomTrunk->GetInstanceCount())
		{
			instancedMushroomTrunk->SetStaticMesh(mushroomTrunk);
			for (int i = instancedMushroomTrunk->GetInstanceCount(); i < lenValue; i++)
			{
				FVector Location = FVector(0.f, 0.f, -flame * i); // 根据需要调整位置
				FTransform InstanceTransform;
				InstanceTransform.SetLocation(Location);

				instancedMushroomTrunk->AddInstance(InstanceTransform);
			}
		}
		
		 if (lenValue< instancedMushroomTrunk->GetInstanceCount())
		{
			for (int i = instancedMushroomTrunk->GetInstanceCount() -1; i >= lenValue; i--)
			{
				instancedMushroomTrunk->RemoveInstance(i);
			}
		}
		 
	}

}

void APlatformerLaunch::TopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCppCharacter* player = Cast<APlatformerCppCharacter>(OtherActor);
	if (player!=nullptr&&SweepResult.ImpactNormal.Z<0)
	{
		player->LaunchCharacter(launchVelocity, false, true);
		timeLine->PlayFromStart();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), launchSound, SweepResult.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),launchPartic, SweepResult.ImpactPoint);
	}
}

// Called every frame
void APlatformerLaunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

