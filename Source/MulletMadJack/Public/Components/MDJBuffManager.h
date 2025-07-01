#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MDJBuffManager.generated.h"

class UMDJEffect;
class ACharacter;
class UMDJEffectBase;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MULLETMADJACK_API UMDJBuffManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UMDJBuffManager();

	UPROPERTY()
	TArray<UMDJEffectBase*> ActiveEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UMDJEffect>> AllEffects;

	UFUNCTION(BlueprintCallable, Category = "Array")
	void ShuffleEffets();

	UFUNCTION(BlueprintCallable, Category = "Array")
	void ApplyEffect(TSubclassOf<UMDJEffect> Effect);

	UFUNCTION(BlueprintCallable, Category = "Array")
	void RemoveEffect(TSubclassOf<UMDJEffect> Effect);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Initialize();

	UPROPERTY()
	ACharacter* OwnerCharacter;

public:
	//Gets
	UFUNCTION(BlueprintCallable, Category = "Effects")
	TArray<UMDJEffectBase*> GetActiveEffects() { return ActiveEffects; };
};
