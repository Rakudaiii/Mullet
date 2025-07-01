#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MDJAIStateTypes.h"
#include "MDJEnemy.generated.h"


//Components
class UCameraComponent;

class UMDJHealthComponent;
class UMDJFightSystemComponent;
class AMDJAIController;

UCLASS()
class MULLETMADJACK_API AMDJEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AMDJEnemy();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMDJHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMDJFightSystemComponent* FightSystemComponent;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TSubclassOf<AMDJAIController> AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Health")
	float Health = 2.0f;

	UFUNCTION(BlueprintCallable, Category = "OnDead")
	void OnDead();

	UFUNCTION(BlueprintCallable, Category = "OnDead")
	void DestroySelf();

};
