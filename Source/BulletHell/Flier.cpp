// Fill out your copyright notice in the Description page of Project Settings.

#include "Flier.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine.h"
#include "BasicProjectile.h"


// Sets default values
AFlier::AFlier() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	IsFiring = false;
	LastFire = 0.f;
	FireDelay = .5f;

	Slowdown = false;
	SlowdownMultiplier = .5f;
	FocusedFireMultiplier = .5f;

	BaseSpeed = 1.f;

	FireLevel = 0;

	MaxFireLevel = 4;

}

// Called when the game starts or when spawned
void AFlier::BeginPlay() {
	Super::BeginPlay();

	Movement->MaxSpeed *= BaseSpeed;

	Movement->Acceleration = Movement->Deceleration = (float)INT_MAX;
	Movement->TurningBoost = 0.f;

	IsFiring = false;
}

// Called every frame
void AFlier::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (IsFiring)
		Fire();
}

// Called to bind functionality to input
void AFlier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFlier::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFlier::MoveRight);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AFlier::EnableFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AFlier::DisableFire);

	PlayerInputComponent->BindAction("Slowdown", EInputEvent::IE_Pressed, this, &AFlier::EnableSlowdown);
	PlayerInputComponent->BindAction("Slowdown", EInputEvent::IE_Released, this, &AFlier::DisableSlowdown);

	PlayerInputComponent->BindAction("DebugIncreaseFireLevel", EInputEvent::IE_Pressed, this, &AFlier::DEBUG_IncreaseFireLevel);
	PlayerInputComponent->BindAction("DebugDecreaseFireLevel", EInputEvent::IE_Pressed, this, &AFlier::DEBUG_DecreaseFireLevel);
}

void AFlier::MoveForward(float Amount) {
	if (Slowdown)
		Amount *= (1 - SlowdownMultiplier);
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AFlier::MoveRight(float Amount) {
	if (Slowdown)
		Amount *= (1 - SlowdownMultiplier);
	AddMovementInput(GetActorRightVector(), Amount);
}

void AFlier::EnableFire() {
	IsFiring = true;
}

void AFlier::DisableFire() {
	IsFiring = false;
	// LastFire = 0.f; // Let player fire semi-auto as fast as they pull the trigger
}

void AFlier::EnableSlowdown() {
	Slowdown = true;
}

void AFlier::DisableSlowdown() {
	Slowdown = false;
}

void AFlier::DEBUG_IncreaseFireLevel() {
	FireLevel++;

	if (FireLevel > MaxFireLevel)
		FireLevel = MaxFireLevel;

	if (GEngine) {
		FString Out = FString::FromInt(FireLevel);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, *Out);
	}
}

void AFlier::DEBUG_DecreaseFireLevel() {
	FireLevel--;
	
	if (FireLevel < 0)
		FireLevel = 0;

	if (GEngine) {
		FString Out = FString::FromInt(FireLevel);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, *Out);
	}
}

void AFlier::Fire(bool Homing) {
	float CurrentTime = GetGameTimeSinceCreation();

	if (CurrentTime > (LastFire + FireDelay)) {

		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		if (Homing) {
			if (HomingProjectileBlueprint) {
				ABasicProjectile* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<ABasicProjectile>(
					HomingProjectileBlueprint,
					SpawnLocation,
					SpawnRotation
				);
			}
		} else {
			if (ProjectileBlueprint) {
				ABasicProjectile* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<ABasicProjectile>(
					ProjectileBlueprint,
					SpawnLocation,
					SpawnRotation
				);
			}
		}

		if (FireLevel >= 1) {
			SideFire(15.f, 50.f, FireLevel >= 4 ? true : false);
		}

		if (FireLevel >= 2) {
			SideFire(7.5f, 25.f, FireLevel >= 4 ? true : false);
		}

		if (FireLevel >= 3) {
			SideFire(90.f, 0.f, FireLevel >= 3 ? true : false);
		}

		LastFire = CurrentTime;
	}
}

void AFlier::SideFire(float RotOffset, float PosOffset, bool Homing) {
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	if (Homing ? HomingProjectileBlueprint : ProjectileBlueprint) {
		SpawnLocation.Y -= PosOffset; // Spawn at left side
		SpawnRotation.Yaw -= (RotOffset * (Slowdown ? (1.f - FocusedFireMultiplier) : 1.f)); // Rotate left

		ABasicProjectile* SpawnedProjectileLeft = (ABasicProjectile*)GetWorld()->SpawnActor<ABasicProjectile>(
			(Homing ? HomingProjectileBlueprint : ProjectileBlueprint),
			SpawnLocation,
			SpawnRotation
		);

		SpawnLocation.Y += (PosOffset * 2); // Counteract earlier subtraction
		SpawnRotation.Yaw += ((RotOffset * 2) * (Slowdown ? (1.f - FocusedFireMultiplier) : 1.f)); // Rotate right, counteracting earlier

		ABasicProjectile* SpawnedProjectileRight = (ABasicProjectile*)GetWorld()->SpawnActor<ABasicProjectile>(
			(Homing ? HomingProjectileBlueprint : ProjectileBlueprint),
			SpawnLocation,
			SpawnRotation
		);
	}
}

