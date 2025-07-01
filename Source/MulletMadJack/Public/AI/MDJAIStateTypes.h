
#pragma once

#include "CoreMinimal.h"
#include "MDJAIStateTypes.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	Shooting        UMETA(DisplayName = "Shooting")
};
