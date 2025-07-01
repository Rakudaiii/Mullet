
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MDJGunDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FGlock
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxAmmo = 7;
	
	
};

UCLASS()
class MULLETMADJACK_API UMDJGunDataAsset : public UDataAsset
{
	GENERATED_BODY()
};
