

#pragma once

#include "CoreMinimal.h"
#include "BasicProjectile.h"
#include "Enemy/EnemyBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "HomingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API AHomingProjectile : public ABasicProjectile
{
	GENERATED_BODY()

public:

	AHomingProjectile();

	UPROPERTY(EditAnywhere)
	UClass* EnemyBaseClass;
	
	virtual void Tick(float DeltaTime) override;

};
