#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJSlowField.generated.h"


UCLASS()
class MULLETMADJACK_API UMDJSlowField : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "SlowField")
	void UseSlowField();


	UPROPERTY()
	FTimerHandle SlowFieldTimerHandle;

	UPROPERTY()
	TMap<ACharacter*, float> OriginalSpeeds;

	UFUNCTION()
	void DrawDebugSlowField(const FVector Start);


	//Data Asset - Parameters
	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetRadius() { return EffectsDataAsset->SlowFieldParameters.Radius; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetSpeedDecrease() { return EffectsDataAsset->SlowFieldParameters.SpeedDecrease; }


	//	//Data Asset - Debug
	UFUNCTION(BlueprintCallable, Category = "SlowField")
	bool GetbDrawDebug() { return EffectsDataAsset->SlowFieldDebug.bDrawDebug; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetSegments() { return EffectsDataAsset->SlowFieldDebug.Segments; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetThickness() { return EffectsDataAsset->SlowFieldDebug.Thickness; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetZOffset() { return EffectsDataAsset->SlowFieldDebug.ZOffset; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	FColor GetColor() { return EffectsDataAsset->SlowFieldDebug.Color; };
};
