#pragma once

#include "CoreMinimal.h"
#include "Actors/Traps/MDJTrapBase.h"
#include "GameFramework/Actor.h"
#include "MDJSpikeTrap.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class MULLETMADJACK_API AMDJSpikeTrap : public AMDJTrapBase
{
	GENERATED_BODY()

public:
	AMDJSpikeTrap();
  
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintCallable, Category = "SpikeTrap")
	void HpDecrease(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			   const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;
  
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 1.0f;
  
	UPROPERTY(EditAnywhere, Category = "SpikeTrap")
	float SpikeDamage = 1.0f;
  
	UPROPERTY()
	FVector MoveDirection = FVector(0, 0, 1); 
  
	UPROPERTY()
	FVector StartLocation;
  
	UPROPERTY()
	float RunningTime = 0.0f;
};
