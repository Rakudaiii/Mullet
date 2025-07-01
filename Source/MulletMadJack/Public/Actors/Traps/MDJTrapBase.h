#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MDJTrapBase.generated.h"

UCLASS()
class MULLETMADJACK_API AMDJTrapBase : public AActor
{
	GENERATED_BODY()

public:
	AMDJTrapBase();

protected:
	virtual void BeginPlay() override;

};
