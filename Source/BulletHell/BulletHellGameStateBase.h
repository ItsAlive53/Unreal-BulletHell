

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BulletHellGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API ABulletHellGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	
public:

	ABulletHellGameStateBase();

protected:

	int Score;

public:

	void IncrementScore();
	int GetScore();


	
};
