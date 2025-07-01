#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJBerserkMode.generated.h"


UCLASS()
class MULLETMADJACK_API UMDJBerserkMode : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

protected:
	UPROPERTY()
	TMap<TWeakObjectPtr<ACharacter>, float> EnemyOriginalSpeeds;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BerserkMode")
	bool bBerserkModeIsActivated = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BerserkMode")
	FTimerHandle BerserkModeTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BerserkMode")
	float CharacterBaseSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BerserkMode")
	float CharacterBaseDashStrength;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BerserkMode")
	float CharacterBaseSlideSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BerserkMode")
	float CharacterBaseGunDamage;

	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	void SaveBaseMovementStats();
	
	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	void CheckHealth();

	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	void UseBerserkMode();

	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	void DeactivateBerserkMode();
	
	

	//Data Asset - Parameters
	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	float GetTriggerHealth() { return EffectsDataAsset->BerserkModeParameters.TriggerHealth; };

	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	float GetMovementSpeedMultiplier() { return EffectsDataAsset->BerserkModeParameters.MovementSpeedMultiplier; };

	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	float GetSlideSpeedMultiplier() { return EffectsDataAsset->BerserkModeParameters.SlideSpeedMultiplier; };

	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	float GetDashSpeedMultiplier() { return EffectsDataAsset->BerserkModeParameters.DashSpeedMultiplier; };
	
	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	float GetGunDamageMultiplier() { return EffectsDataAsset->BerserkModeParameters.GunDamageMultiplier; };
	
	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	float GetSpeedDecrease() { return EffectsDataAsset->BerserkModeParameters.SpeedDecrease; };
public:
	//Gets
	UFUNCTION(BlueprintCallable, Category = "BerserkMode")
	bool GetbBerserkModeIsActivated() { return bBerserkModeIsActivated; };

private:
	UFUNCTION()
	void DebugLog() const;
};
