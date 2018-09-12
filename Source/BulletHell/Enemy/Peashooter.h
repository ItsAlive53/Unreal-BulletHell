

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Peashooter.generated.h"

UCLASS()
class BULLETHELL_API APeashooter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeashooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
