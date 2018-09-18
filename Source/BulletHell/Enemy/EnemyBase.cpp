

#include "EnemyBase.h"


// Sets default values
AEnemyBase::AEnemyBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HP = 1;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay() {
	Super::BeginPlay();

}

void AEnemyBase::FinishDestroy() {
	if (GEngine) {
		FString Out = "Enemy destroy test";
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, *Out);
	}

	Super::FinishDestroy();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AEnemyBase::Die() {
	BeginDestroy();

	FinishDestroy();
}

void AEnemyBase::Damage() {
	HP--;

	if (HP <= 0) {
		Die();
	}
}

