#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJDeflectShield.generated.h"

UCLASS()
class MULLETMADJACK_API UMDJDeflectShield : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DeflectShield")
	FTimerHandle DeflectShieldTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DeflectShield")
	float Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DeflectShield")
	float PastTime;


	UFUNCTION(BlueprintCallable, Category = "DeflectShield")
	void StartTimer();

	//Data Asset
	UFUNCTION(BlueprintCallable, Category = "DeflectShield")
	int32 GetMinChance() { return EffectsDataAsset->DeflectShield.MinChance; };
	
	UFUNCTION(BlueprintCallable, Category = "DeflectShield")
	int32 GetMaxChance() { return EffectsDataAsset->DeflectShield.MaxChance; };

	UFUNCTION(BlueprintCallable, Category = "DeflectShield")
	float GetDurationTime() { return EffectsDataAsset->DeflectShield.DurationTime; };
};
