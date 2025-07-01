
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MDJAcidTrap.generated.h"

UCLASS()
class MULLETMADJACK_API AMDJAcidTrap : public AActor
{
	GENERATED_BODY()

public:
	AMDJAcidTrap();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
