

#include "EnemyBase.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"


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

// Called every frame
void AEnemyBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AEnemyBase::Die() {
	ABulletHellGameStateBase* Gamestate = (ABulletHellGameStateBase*)GetWorld()->GetGameState();
	Gamestate->IncrementScore();

	Destroy();
}

void AEnemyBase::Damage() {
	HP--;

	if (HP <= 0) {
		Die();
	}
}

void AEnemyBase::SetHP(float HP) {
	this->HP = HP;
}

