

#include "WallEnemy.h"
#include "Engine/StaticMesh.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

AWallEnemy::AWallEnemy() {
	ScaleMultiplier = .8f;
}

void AWallEnemy::Damage() {
	Super::Damage();

	UStaticMeshComponent* Mesh = (UStaticMeshComponent*)GetComponentByClass(UStaticMeshComponent::StaticClass());

	if (Mesh) {
		Mesh->SetRelativeScale3D(Mesh->RelativeScale3D * ScaleMultiplier);
	}
}

