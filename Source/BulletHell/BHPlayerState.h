

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BHPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API ABHPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	
public:

	ABHPlayerState();

	void IncrementScore();
	int GetScore();
	
protected:

	int Score;

};
