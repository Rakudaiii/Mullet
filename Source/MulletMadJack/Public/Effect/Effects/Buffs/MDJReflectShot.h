#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJReflectShot.generated.h"


UCLASS()
class MULLETMADJACK_API UMDJReflectShot : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "ReflectShot")
	void UseReflectShot(AActor* DamagedActor);

	//Data Asset
	UFUNCTION(BlueprintCallable, Category = "ReflectShot")
	int32 GetChance() { return EffectsDataAsset->ReflectShotParameters.Chance; };
};
