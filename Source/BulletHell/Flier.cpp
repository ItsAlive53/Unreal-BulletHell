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

	CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	IsFiring = false;
	LastFire = 0.f;
	FireDelay = .5f;

	Slowdown = false;
	SlowdownMultiplier = .5f;

}

// Called when the game starts or when spawned
void AFlier::BeginPlay() {
	Super::BeginPlay();

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
}

void AFlier::MoveForward(float Amount) {
	if (Slowdown)
		Amount *= SlowdownMultiplier;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AFlier::MoveRight(float Amount) {
	if (Slowdown)
		Amount *= SlowdownMultiplier;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AFlier::EnableFire() {
	IsFiring = true;
}

void AFlier::DisableFire() {
	IsFiring = false;
	LastFire = 0.f; // Let player fire semi-auto as fast as they pull the trigger
}

void AFlier::EnableSlowdown() {
	Slowdown = true;
}

void AFlier::DisableSlowdown() {
	Slowdown = false;
}

void AFlier::Fire() {
	// TODO: Spawn Projectile

	float CurrentTime = GetGameTimeSinceCreation();

	if (CurrentTime > (LastFire + FireDelay)) {
		if (GEngine) {
			FString Out = "Fired at ";
			FString GameTime = FString::SanitizeFloat(GetGameTimeSinceCreation());
			Out.Append(*GameTime);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, *Out);
		}

		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		if (GEngine) {
			FString Out = "Blep again.";
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, *Out);
		}
		if (ProjectileBlueprint) {
			if (GEngine) {
				FString Out = "Did we blep here?";
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, *Out);
			}
			ABasicProjectile* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<ABasicProjectile>(
				ProjectileBlueprint,
				SpawnLocation,
				SpawnRotation
			);
		}

		LastFire = CurrentTime;
	}
}

