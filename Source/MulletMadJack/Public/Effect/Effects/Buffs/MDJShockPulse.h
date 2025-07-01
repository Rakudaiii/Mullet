#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJShockPulse.generated.h"


UCLASS()
class MULLETMADJACK_API UMDJShockPulse : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	void UseShockPulse(AActor* DamagedActor);

protected:
	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	void DrawDebugShockPulse(const FVector Start);


	//Data Asset - Parameters
	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	float GetRadius() { return EffectsDataAsset->ShockPulseParameters.Radius; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	float GetShockPulseDamage() { return EffectsDataAsset->ShockPulseParameters.Damage; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	int32 GetChance() { return EffectsDataAsset->ShockPulseParameters.Chance; };


	//Data Asset - Debug
	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	bool GetbDrawDebug() { return EffectsDataAsset->ShockPulseDebug.bDrawDebug; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	float GetSegments() { return EffectsDataAsset->ShockPulseDebug.Segments; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	float GetLifeTime() { return EffectsDataAsset->ShockPulseDebug.LifeTime; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	FColor GetColor() { return EffectsDataAsset->ShockPulseDebug.Color; };
};
