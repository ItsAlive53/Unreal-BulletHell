

#include "Peashooter.h"


// Sets default values
APeashooter::APeashooter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APeashooter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APeashooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

