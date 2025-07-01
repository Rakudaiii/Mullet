#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MDJParkourMovementComponent.generated.h"

class UCharacterMovementComponent;


DECLARE_LOG_CATEGORY_EXTERN(ParkourMovementComponent, Log, All);

//Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlidding);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MULLETMADJACK_API UMDJParkourMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMDJParkourMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSlidding OnSlidding;

	UFUNCTION(BlueprintCallable, Category = "WallRun")
	void LandEvent();


	UFUNCTION(BlueprintCallable, Category = "Dash")
	void Dash();

	UFUNCTION(BlueprintCallable, Category = "Slide")
	void Slide();

	UFUNCTION(BlueprintCallable, Category = "Jump")
	void StartJump();

	UFUNCTION(BlueprintCallable, Category = "Jump")
	void StopJump();

protected:
	virtual void BeginPlay() override;
	void Initialize();

	UPROPERTY(BlueprintReadOnly, Category = "Component")
	ACharacter* Character;

	UPROPERTY(BlueprintReadOnly, Category = "Component")
	UCharacterMovementComponent* CharacterMovementComponent;

	// --------- WallRun ---------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool bCanWallRun = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallRun")
	float WallRunSpeed = 850.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallRun")
	float WallRunJumpHeight = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallRun")
	float WallRunJumpOffForce = 300.0f;

	UPROPERTY()
	float WallRunTargetGravity = 0.25f;

	UPROPERTY()
	float DefaultGravity;

	UPROPERTY()
	FVector WallRunNormal;

	UPROPERTY()
	FVector Right;

	UPROPERTY()
	FVector Left;

	UPROPERTY()
	FTimerHandle FTResetWallRunSuppresstion;

	UPROPERTY()
	bool bWallRunGravity;

	UPROPERTY()
	bool bIsWallRunning;

	UPROPERTY()
	bool bWallRunningR;

	UPROPERTY()
	bool bWallRunningL;

	UPROPERTY()
	bool bWallRunSuppressed;

	UFUNCTION(Blueprintable, Category = "WallRun")
	void JumpEvent();

	UFUNCTION(Blueprintable, Category = "WallRun")
	void InitializeWallRun();

	UFUNCTION(Blueprintable, Category = "WallRun")
	void WallRunUpdate();

	UFUNCTION(Blueprintable, Category = "WallRun")
	bool WallRunMovement(const FVector Start, const FVector End, const float WallRunDirection);

	UFUNCTION(Blueprintable, Category = "WallRun")
	void WallRunEnd(const float ResetTime);

	UFUNCTION(Blueprintable, Category = "WallRun")
	void SuppressWallRun(const float Delay);

	UFUNCTION(Blueprintable, Category = "WallRun")
	void CameraTick();

	UFUNCTION(Blueprintable, Category = "WallRun")
	void CameraTilt(const float TargetRollAngle);

	UFUNCTION(Blueprintable, Category = "WallRun")
	void WallRunJump();

	UFUNCTION(Blueprintable, Category = "WallRun")
	void WallRunUpdateEvent();

	UFUNCTION(Blueprintable, Category = "WallRun")
	void ResetWallRunSuppresstion();

	UFUNCTION(Blueprintable, Category = "WallRun")
	void WallRunEndVectors(FVector& OutRight, FVector& OutLeft);

	UFUNCTION(Blueprintable, Category = "WallRun")
	bool ValidWallRunVector(const FVector InVector);


	UFUNCTION(Blueprintable, Category = "WallRun")
	FVector PlayerToWallVector();

	// --------- Dash ---------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool bCanDash = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashStrength = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashTimeReload = 0.3f;

	UPROPERTY()
	bool bIsDashing = false;

	UFUNCTION(Blueprintable, Category = "Dash")
	void ReloadDash();

	UFUNCTION(Blueprintable, Category = "Dash")
	void ReloadingDash();

	// --------- Slide ---------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool bCanSlide = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	bool bSlideHasBuff = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float SlideDuration = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float SlideSpeed = 800.0f;

	UPROPERTY()
	float SlideFriction = 0.1f;

	UPROPERTY()
	bool bIsSliding = false;

	UPROPERTY()
	float NormalSpeed;

	UPROPERTY()
	float NormalFriction;

	UPROPERTY()
	float SlideDeceleration;

	UPROPERTY()
	float NormalDeceleration;

	UPROPERTY()
	float SlideCapsuleHalfHeight;

	UPROPERTY()
	float NormalCapsuleHalfHeight;

	UFUNCTION(Blueprintable, Category = "Slide")
	void InitializeSlide();

	UFUNCTION(Blueprintable, Category = "Slide")
	void StartSlide();

	UFUNCTION(Blueprintable, Category = "Slide")
	void StopSlide();

	// --------- Jump ---------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool bCanJump = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
	float JumpZVelocity = 420.0f;

	UPROPERTY()
	bool bIsJumping = false;

	UFUNCTION(Blueprintable, Category = "Jump")
	void InitializeJump();

public:
	//Gets
	UFUNCTION(BlueprintCallable, Category = "Getters")
	bool GetIsDashing() { return bIsDashing; };

	UFUNCTION(BlueprintCallable, Category = "Getters")
	bool GetIsJumping() { return bIsJumping; };

	UFUNCTION(BlueprintCallable, Category = "Getters")
	bool GetIsSliding() { return bIsSliding; };

	UFUNCTION(BlueprintCallable, Category = "Getters")
	bool GetIsWallRunning() { return bIsWallRunning; };

	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetSlideSpeed() { return SlideSpeed; };

	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetDashStrength() { return DashStrength; };

	//Sets
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetbSlideHasBuff(bool NewbSlideHasBuff) { bSlideHasBuff = NewbSlideHasBuff; };

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDashStrength(const float NewDashStrength) { DashStrength = NewDashStrength; };

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetSlideSpeed(const float NewSlideSpeed) { SlideSpeed = NewSlideSpeed; };
};
