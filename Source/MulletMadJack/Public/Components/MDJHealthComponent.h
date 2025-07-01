#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MDJHealthComponent.generated.h"

//Log
DECLARE_LOG_CATEGORY_EXTERN(HealthComponent, Log, All);

//Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamageDelegate, AActor*, DamagedActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float, CurrentHealth);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MULLETMADJACK_API UMDJHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMDJHealthComponent();

	UFUNCTION(Category = "Component")
	void Initialize(const float InHealth);


	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeadDelegate OnDead;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTakeDamageDelegate OnTakeDamage;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedDelegate OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(const float InDamage, AActor* DamagedActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void GainHealth(const float InValue);

	UFUNCTION(Category = "Health")
	bool IsDead(const float InHealth);

	UFUNCTION()
	void EnableGodMode(FName BuffName, float Duration, float Chance = 100);

protected:
	virtual void BeginPlay() override;


	//Category - Health
	UPROPERTY()
	TSet<FName> ActiveGodModeSources;

	UPROPERTY()
	TMap<FName, FTimerHandle> GodModeTimers;
	
	UPROPERTY()
	float CurrenHealth;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY()
	bool bDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bGodMode = false;

	//Category - AutoHealthDecrease
	UFUNCTION(Category = "AutoHealthDecrease")
	void StartAutoHPDecrease();

	UFUNCTION(Category = "AutoHealthDecrease")
	void StopAutoHPDecrease();

	UFUNCTION(Category = "AutoHealthDecrease")
	void HPDecrease();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoHealthDecrease")
	bool bAutoTickHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoHealthDecrease")
	float TickTime = 1.0f;

	UPROPERTY()
	FTimerHandle HPDecreaseTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoHealthDecrease")
	float TickDamage = 1.0f;

public:
	//Sets
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetbGodMode(bool NewbGodMode) { bGodMode = NewbGodMode; };

	//Gets
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool GetbGodMode() { return bGodMode; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() { return CurrenHealth; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() { return MaxHealth; };
};
