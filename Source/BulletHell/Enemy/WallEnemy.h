

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "Engine/StaticMesh.h"
#include "WallEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API AWallEnemy : public AEnemyBase {
	GENERATED_BODY()

public:

	AWallEnemy();

	UPROPERTY(EditAnywhere)
	float ScaleMultiplier;

	virtual void Damage() override;
	
	
};
