#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJGhostSlide.generated.h"


UCLASS()
class MULLETMADJACK_API UMDJGhostSlide : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

	UFUNCTION(BlueprintCallable, Category = "GhostSlide")
	void UseGhostSlide();

protected:
	UPROPERTY()
	TArray<AActor*> OutActors;

	UFUNCTION(BlueprintCallable, Category = "GhostSlide")
	void DrawDebugGhostSlide(const FVector Start);
	
	//Data Asset - Parameters
	UFUNCTION(BlueprintCallable, Category = "GhostSlide")
	int32 GetChance() { return EffectsDataAsset->GhostSlideParameters.Chance; };

	UFUNCTION(BlueprintCallable, Category = "GhostSlide")
	float GetRadius() { return EffectsDataAsset->GhostSlideParameters.Radius; };

	//Data Asset - Debug
	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	bool GetbDrawDebug() { return EffectsDataAsset->GhostSlideDebug.bDrawDebug; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	float GetSegments() { return EffectsDataAsset->GhostSlideDebug.Segments; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	float GetLifeTime() { return EffectsDataAsset->GhostSlideDebug.LifeTime; };

	UFUNCTION(BlueprintCallable, Category = "ShockPulse")
	FColor GetColor() { return EffectsDataAsset->GhostSlideDebug.Color; };
};
