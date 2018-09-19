

#pragma once

#include "CoreMinimal.h"
#include "BasicProjectile.h"
#include "Enemy/EnemyBase.h"
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
	
	virtual void Tick(float DeltaTime) override;

};
