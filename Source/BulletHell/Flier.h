// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine.h"
#include "BasicProjectile.h"
#include "HomingProjectile.h"
#include "Flier.generated.h"

UCLASS()
class BULLETHELL_API AFlier : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlier();

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABasicProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHomingProjectile> HomingProjectileBlueprint;

	UPROPERTY(EditAnywhere)
	float FireDelay;

	UPROPERTY(EditAnywhere)
	float SlowdownMultiplier;

	UPROPERTY(EditAnywhere)
	float FocusedFireMultiplier;

	UPROPERTY(EditAnywhere)
	float BaseSpeed;

	UPROPERTY(EditAnywhere)
	int MaxFireLevel;

protected:
	bool IsFiring;
	float LastFire;

	bool Slowdown;

	int FireLevel;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	
	void EnableFire();
	void DisableFire();

	void EnableSlowdown();
	void DisableSlowdown();

	void DEBUG_IncreaseFireLevel();
	void DEBUG_DecreaseFireLevel();

	void Fire(bool Homing = false);

	void SideFire(float RotOffset, float PosOffset, bool Homing = false);

};
