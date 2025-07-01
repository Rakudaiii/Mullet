
#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJAutoAimAssist.generated.h"

UCLASS()
class MULLETMADJACK_API UMDJAutoAimAssist : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect() override;

protected:
	void TickAutoAim();
	AActor* FindClosestTarget();

	UPROPERTY(EditDefaultsOnly, Category = "AutoAim")
	float Radius = 1500.f;

	UPROPERTY(EditDefaultsOnly, Category = "AutoAim")
	float TickRate = 0.1f;

	FTimerHandle AutoAimTimerHandle;
};
