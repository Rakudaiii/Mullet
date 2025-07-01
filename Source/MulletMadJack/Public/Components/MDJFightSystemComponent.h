#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MDJFightSystemComponent.generated.h"

class UMDJGunBase;
//Log
DECLARE_LOG_CATEGORY_EXTERN(FightSystemComponent, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFire, AActor*, HitActor);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MULLETMADJACK_API UMDJFightSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMDJFightSystemComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnFire OnFire;
	

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void EquipGun(TSubclassOf<UMDJGunBase> GunClass);

	UFUNCTION(BlueprintCallable)
	void StartFiring();
	
	UFUNCTION(BlueprintCallable)
	void StopFiring();

	UFUNCTION(BlueprintCallable)
	void ReloadGun();

protected:
	virtual void BeginPlay() override;

	//Setup component
	UPROPERTY(BlueprintReadOnly, Category = "Component")
	ACharacter* Character;

	UFUNCTION(BlueprintCallable, Category = "Component")
	void Initialize();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool bCanKick = true;

	// ------------ Shoot ------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool bCanShoot = true;

	UPROPERTY()
	UMDJGunBase* CurrentGun;

	

public:
	//Gets
	UFUNCTION(BlueprintCallable, Category = "Shoot")
	bool GetbCanShoot() { return bCanShoot; };



	UFUNCTION(BlueprintPure, Category = "Shoot")
	UMDJGunBase* GetCurrentGun() const { return CurrentGun; };

	//Sets
	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void SetbCanShoot(const bool bNewCanShoot) { bCanShoot = bNewCanShoot; };

	
};
