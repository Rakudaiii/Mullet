#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MDJMainCharacter.generated.h"

//Input
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


//Components
class UCameraComponent;

class UMDJFightSystemComponent;
class UMDJHealthComponent;
class UMDJParkourMovementComponent;
class UMDJBuffManager;

//Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterLandedDelegate);


UCLASS()
class AMDJMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMDJMainCharacter();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterLandedDelegate OnCharacterLanded;

	
protected:

	UFUNCTION()
	void InitializeComponets();

	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(Category = "Dead")
	void OnDead();

	
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	//Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SlideAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ReloadAction;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
	//Varibales
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float Health = 10.0f;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMDJFightSystemComponent* FightSystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMDJHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMDJParkourMovementComponent* ParkourMovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMDJBuffManager* BuffManager;
};
