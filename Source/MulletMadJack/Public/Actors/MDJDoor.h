#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "MDJDoor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UCurveFloat;

UCLASS()
class MULLETMADJACK_API AMDJDoor : public AActor
{
	GENERATED_BODY()

public:
	AMDJDoor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* LeftDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Door|Timeline")
	UCurveFloat* DoorCurve;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorMoveDistance = 150.0f;

private:
	FTimeline DoorTimeline;

	FVector LeftInitialLocation;
	FVector RightInitialLocation;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					   const FHitResult& SweepResult);

	UFUNCTION()
	void HandleDoorProgress(float Value);

	void OpenDoor();
};
