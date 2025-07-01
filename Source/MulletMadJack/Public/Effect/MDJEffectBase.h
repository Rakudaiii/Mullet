#pragma once

#include "CoreMinimal.h"
#include "Effects/Buffs/DataAsset/MDJEffectsDataAsset.h"
#include "MDJEffect.h"
#include "MDJEffectBase.generated.h"


//Log
DECLARE_LOG_CATEGORY_EXTERN(Effects, Log, All);

class AMDJMainCharacter;

UCLASS()
class MULLETMADJACK_API UMDJEffectBase : public UMDJEffect
{
	GENERATED_BODY()

public:
	UMDJEffectBase();

	UFUNCTION(BlueprintCallable)
	void BaseInitialize(AActor* Actor);


	UFUNCTION(BlueprintCallable)
	virtual void ApplyEffect();

protected:
	UFUNCTION(BlueprintCallable)
	bool GetRemoveAllDebug() { return EffectsDataAsset->RemoveAllDebug; };

	UPROPERTY()
	AMDJMainCharacter* MainCharacter;

	UPROPERTY()
	ACharacter* Character;

	UPROPERTY()
	TObjectPtr<UMDJEffectsDataAsset> EffectsDataAsset;
};
