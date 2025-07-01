#pragma once

#include "CoreMinimal.h"
#include "Effect/MDJEffectBase.h"
#include "MDJGunBase.generated.h"

class AMDJBullet;

DECLARE_LOG_CATEGORY_EXTERN(Gun, Log, All);

UCLASS()
class MULLETMADJACK_API UMDJGunBase : public UMDJEffectBase
{
	GENERATED_BODY()

public:
	UMDJGunBase();
	virtual void ApplyEffect() override;

	UFUNCTION(BlueprintCallable)
	void Init(ACharacter* InCharacter);

	UFUNCTION(BlueprintCallable)
	void StartFiring();

	UFUNCTION(BlueprintCallable)
	void StopFiring();

	UFUNCTION(BlueprintCallable)
	void ReloadAmmo(bool bManual = true);

	UFUNCTION(BlueprintCallable)
	void SetGunDamage(float InNewGunDamage) { GunDamage = InNewGunDamage; }

protected:
	// === Owner ===
	UPROPERTY() ACharacter* OwnerCharacterGun = nullptr;

	// === Firing ===
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	bool bIsAuto = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float FireRate = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float GunDamage = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	bool bUseProjectile = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	bool bIsShotGun = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float Pellets = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float MaxRange = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float SpreadAngle = 0.0f;

	UPROPERTY()
	FTimerHandle AutoFireHandle;

	UFUNCTION()
	void Fire();

	// === Reloading ===
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Reload")
	float ReloadTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Reload")
	int32 MaxAmmo = 6;

	UPROPERTY(BlueprintReadOnly, Category="Gun|Reload")
	int32 CurrentAmmo = 0;

	UPROPERTY(BlueprintReadOnly, Category="Gun|Reload")
	bool bIsReloading = false;

	UPROPERTY(BlueprintReadOnly, Category="Gun|Reload")
	bool bIsManualReloading = false;

	UPROPERTY()
	FTimerHandle ReloadHandle;

	UFUNCTION()
	void CompleteReload();

	// === Gun Data ===
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	TSubclassOf<UMDJGunBase> GunClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	TSubclassOf<AMDJBullet> BulletClass;

public:
	// === Getters ===
	UFUNCTION(BlueprintPure) int32 GetCurrentAmmo() const { return CurrentAmmo; }
	UFUNCTION(BlueprintPure) int32 GetMaxAmmo() const { return MaxAmmo; }
	UFUNCTION(BlueprintPure) bool IsReloading() const { return bIsReloading; }
	UFUNCTION(BlueprintPure) float GetGunDamage() const { return GunDamage; }
	UFUNCTION(BlueprintPure) bool GetUseProjectile() const { return bUseProjectile; }
	UFUNCTION(BlueprintPure) ACharacter* GetOwnerCharacter() const { return OwnerCharacterGun; }
	UFUNCTION(BlueprintPure) float GetFireRate() const { return FireRate; }
	UFUNCTION(BlueprintPure) bool GetIsShotGun() const { return bIsShotGun; }
	UFUNCTION(BlueprintPure) float GetPellets() const { return Pellets; }
	UFUNCTION(BlueprintPure) float GetMaxRange() const { return MaxRange; }
	UFUNCTION(BlueprintPure) float GetSpreadAngle() const { return SpreadAngle; }
	UFUNCTION(BlueprintPure) float GetTimeRemaining() const
	{
		return GetWorld()->GetTimerManager().IsTimerActive(ReloadHandle)
			? FMath::RoundToFloat(GetWorld()->GetTimerManager().GetTimerRemaining(ReloadHandle) * 10.f) / 10.f
			: 0.f;
	}
};
