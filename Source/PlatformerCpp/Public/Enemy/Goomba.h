// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Goomba.generated.h"


UCLASS()
class PLATFORMERCPP_API AGoomba : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGoomba();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collider")
	TObjectPtr<USphereComponent>collider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerDetectRange")
	TObjectPtr<USphereComponent>playerDetectRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StompBox")
	TObjectPtr<UBoxComponent>stompBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook")
	TObjectPtr<UPaperFlipbookComponent>flipBook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Squish")
	TObjectPtr<USoundBase>squish;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireSquish")
	TObjectPtr<USoundBase>fireSquish;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ParticleGoomba")
	TObjectPtr<UParticleSystem> particleGoomba;

	//被火球击杀后的移动和旋转

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitValue")
	int hitValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Points")
	int points;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipbookPlayRate")
	float flipbookPlayRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bIsLeft")
	bool bIsLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bmoveMent")
	bool bmoveMent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "bIsSeekEnemy")
	bool bIsSeekEnemy;

	FTimerHandle timeHanndle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void ColliderBedginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void DetectBedginOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void DetectEndOverlop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void StompBoxOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	UFUNCTION()
	void ColliderOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void CylinderOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void DestroyGoomba();
	UFUNCTION()
	void UpdataPoints();

};

