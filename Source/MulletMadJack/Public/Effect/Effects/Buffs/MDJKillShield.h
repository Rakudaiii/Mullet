#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJKillShield.generated.h"

UCLASS()
class MULLETMADJACK_API UMDJKillShield : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "KillShield")
	void UseKillShield(AActor* HitActor);
	

	//Data Asset
	UFUNCTION(BlueprintCallable, Category = "KillShield")
	int32 GetChance() { return EffectsDataAsset->KillShieldParameters.Chance; };

	UFUNCTION(BlueprintCallable, Category = "KillShield")
	float GetResetTime() { return EffectsDataAsset->KillShieldParameters.ResetTime; };
};
