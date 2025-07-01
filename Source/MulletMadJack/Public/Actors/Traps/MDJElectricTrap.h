#pragma once

#include "CoreMinimal.h"
#include "Actors/Traps/MDJTrapBase.h"
#include "GameFramework/Actor.h"
#include "MDJElectricTrap.generated.h"


class UBoxComponent;

UCLASS()
class MULLETMADJACK_API AMDJElectricTrap : public AMDJTrapBase
{
	GENERATED_BODY()

public:
	AMDJElectricTrap();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ElectricTrap")
	float TickTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ElectricTrap")
	float ElectricTrapDamge = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "ElectricTrap")
	void UseElectricTrap();
};
