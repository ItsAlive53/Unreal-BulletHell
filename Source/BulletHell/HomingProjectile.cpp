

#include "HomingProjectile.h"
#include "Enemy/EnemyBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AHomingProjectile::AHomingProjectile() {
	ProjectileMovement->bIsHomingProjectile = (uint32)1;
}

void AHomingProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ProjectileMovement->HomingAccelerationMagnitude = ProjectileMovement->InitialSpeed * 10.f;

	if (ProjectileMovement->HomingTargetComponent.Get() == NULL) {
		TArray<AActor*> Enemies;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), Enemies);

		if (Enemies.Num() == 0) return;

		int i = rand() % Enemies.Num();
		
		if (Enemies.IsValidIndex(i)) {
			AEnemyBase* Enemy = (AEnemyBase*)Enemies[i];
			// TWeakObjectPtr<USceneComponent*> Target = new TWeakObjectPtr(Enemy->RootComponent);

			ProjectileMovement->HomingTargetComponent = Enemy->GetRootComponent();
		}
	}
}
