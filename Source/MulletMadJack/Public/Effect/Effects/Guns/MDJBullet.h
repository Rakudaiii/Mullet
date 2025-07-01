#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MDJBullet.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UBoxComponent;


UCLASS()
class MULLETMADJACK_API AMDJBullet : public AActor
{
	GENERATED_BODY()

public:
	AMDJBullet();

	UFUNCTION(BlueprintCallable)
	void Initialize();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	ACharacter* OwnerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	UStaticMeshComponent* BulletStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY()
	bool bUseProjectile = false;

	UPROPERTY()
	float Damage = 0.0f;

	//ShotGun

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	bool bIsShotGun = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float Pellets = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float MaxRange = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun|Fire")
	float SpreadAngle = 0.0f;

	UFUNCTION()
	void UseSingleTrace();

	UFUNCTION()
	void UseMiltyTrace();

	UFUNCTION()
	void UseProjectile();

	UFUNCTION()
	void example(const bool bHit, const FHitResult Hit, const FVector Start, const FVector End);
};
