

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BulletHellHUD.generated.h"
#include "HUD/HealthBar.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API ABulletHellHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	HealthBar* hpBar;
	
	ABulletHellHUD();
	
};
