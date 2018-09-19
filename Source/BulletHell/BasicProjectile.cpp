

#include "BasicProjectile.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> Overlapped;
	GetOverlappingActors(Overlapped, AEnemyBase::StaticClass());

	if (Overlapped.IsValidIndex(0)) {
		if (GEngine) {
			FString Out = "internal screaming";
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, *Out);
		}

		AEnemyBase* Enemy = (AEnemyBase*)Overlapped[0];
		Enemy->Damage();

		Destroy();
	}
}

