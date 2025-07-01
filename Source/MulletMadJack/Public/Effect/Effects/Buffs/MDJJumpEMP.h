#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJJumpEMP.generated.h"


UCLASS()
class MULLETMADJACK_API UMDJJumpEMP : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "JumpEMP")
	void UseJumpEMP();

	UFUNCTION(BlueprintCallable, Category = "JumpEMP")
	void StartResetDebuff();

	UFUNCTION(BlueprintCallable, Category = "JumpEMP")
	void ResetDebuff();

	UPROPERTY()
	TArray<AActor*> OutActors;

	UFUNCTION()
	void DrawDebugShockPulse(const FVector Start);

	//Data Asset - Parameters
	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetRadius() { return EffectsDataAsset->JumpEmpParameters.Radius; }

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	int32 GetChance() { return EffectsDataAsset->JumpEmpParameters.Chance; }

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetResetTime() { return EffectsDataAsset->JumpEmpParameters.ResetTime; }


	//Data Asset - Debug
	UFUNCTION(BlueprintCallable, Category = "SlowField")
	bool GetbDrawDebug() { return EffectsDataAsset->JumpEmpDebug.bDrawDebug; }

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetSegments() { return EffectsDataAsset->JumpEmpDebug.Segments; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetLifeTime() { return EffectsDataAsset->JumpEmpDebug.LifeTime; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetThickness() { return EffectsDataAsset->JumpEmpDebug.Thickness; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	float GetZOffset() { return EffectsDataAsset->JumpEmpDebug.ZOffset; };

	UFUNCTION(BlueprintCallable, Category = "SlowField")
	FColor GetColor() { return EffectsDataAsset->JumpEmpDebug.Color; };
};
