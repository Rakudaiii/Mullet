#include "MulletMadJack/Public/Components/MDJParkourMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Effect/MDJEffectBase.h"

DEFINE_LOG_CATEGORY(ParkourMovementComponent);

UMDJParkourMovementComponent::UMDJParkourMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMDJParkourMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize();
}

void UMDJParkourMovementComponent::Initialize()
{
	Character = Cast<ACharacter>(GetOwner());
	CharacterMovementComponent = Character->GetCharacterMovement();


	InitializeWallRun();
	InitializeSlide();
	InitializeJump();
}


void UMDJParkourMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CameraTick();
}


// --------- WallRun ---------
void UMDJParkourMovementComponent::JumpEvent()
{
	WallRunJump();
}

void UMDJParkourMovementComponent::LandEvent()
{
	WallRunEnd(0.0f);
	bWallRunSuppressed = false;
}

void UMDJParkourMovementComponent::InitializeWallRun()
{
	if (bCanWallRun)
	{
		UE_LOG(ParkourMovementComponent, Log, TEXT("Initialize Wall Run was successful"));
		DefaultGravity = CharacterMovementComponent->GravityScale;

		FTimerHandle temp;
		GetWorld()->GetTimerManager().SetTimer(temp, this, &UMDJParkourMovementComponent::WallRunUpdateEvent, 0.2f,
		                                       true);
	}
	else
	{
		UE_LOG(ParkourMovementComponent, Log, TEXT("Initialize Wall Run wasn't successful"));
	}
}

void UMDJParkourMovementComponent::WallRunUpdate()
{
	if (bCanWallRun)
	{
		FVector Start = Character->GetActorLocation();

		float CharacterGravityScale = CharacterMovementComponent->GravityScale;

		WallRunEndVectors(Right, Left);
		if (WallRunMovement(Start, Right, -1.0f))
		{
			bIsWallRunning = true;
			bWallRunningR = true;
			bWallRunningL = false;

			CharacterMovementComponent->GravityScale = FMath::FInterpTo(CharacterGravityScale, WallRunTargetGravity,
			                                                            GetWorld()->GetDeltaSeconds(), 10.0f);
		}
		else
		{
			if (bWallRunningR)
			{
				WallRunEnd(1.0f);
			}
			else
			{
				WallRunEndVectors(Right, Left);
				if (WallRunMovement(Start, Left, 1.0f))
				{
					bIsWallRunning = true;
					bWallRunningR = false;
					bWallRunningL = true;

					CharacterMovementComponent->GravityScale = FMath::FInterpTo(
						CharacterGravityScale, WallRunTargetGravity, GetWorld()->GetDeltaSeconds(), 10.0f);
				}
				else
				{
					WallRunEnd(1.0f);
				}
			}
		}
	}
}

bool UMDJParkourMovementComponent::WallRunMovement(const FVector Start, const FVector End, const float WallRunDirection)
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	if (Hit.bBlockingHit)
	{
		if (ValidWallRunVector(Hit.Normal) && CharacterMovementComponent->IsFalling())
		{
			WallRunNormal = Hit.Normal;

			Character->LaunchCharacter(PlayerToWallVector(), false, false);

			float WallRunVelocity = WallRunDirection * WallRunSpeed;
			FVector LaunchVector = WallRunNormal.Cross(FVector(0.0f, 0.0f, 1.0f)) * WallRunVelocity;
			Character->LaunchCharacter(LaunchVector, true, !bWallRunGravity);

			return true;
		}
	}

	return false;
}

void UMDJParkourMovementComponent::WallRunEnd(const float ResetTime)
{
	if (bIsWallRunning)
	{
		bIsWallRunning = false;
		bWallRunningR = false;
		bWallRunningL = false;
		CharacterMovementComponent->GravityScale = DefaultGravity;

		SuppressWallRun(ResetTime);
	}
}

void UMDJParkourMovementComponent::SuppressWallRun(const float Delay)
{
	bWallRunSuppressed = true;


	GetWorld()->GetTimerManager().SetTimer(FTResetWallRunSuppresstion, this,
	                                       &UMDJParkourMovementComponent::ResetWallRunSuppresstion, Delay,
	                                       false);
}

void UMDJParkourMovementComponent::CameraTick()
{
	const float TiltAngle = bWallRunningL ? 15.0f : (bWallRunningR ? -15.0f : 0.0f);
	CameraTilt(TiltAngle);
}

void UMDJParkourMovementComponent::CameraTilt(const float TargetRollAngle)
{
	FRotator CurrentRotation = Character->GetController()->GetControlRotation();
	FRotator TargetRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, TargetRollAngle);

	FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, TargetRotation,
	                                             GetWorld()->GetDeltaSeconds(), 10.0f);

	Character->GetController()->SetControlRotation(SmoothedRotation);
}

void UMDJParkourMovementComponent::WallRunJump()
{
	if (bIsWallRunning)
	{
		WallRunEnd(0.35f);

		FVector LaunchVector = FVector(WallRunJumpOffForce * WallRunNormal.X, WallRunJumpOffForce * WallRunNormal.Y,
		                               WallRunJumpHeight);
		Character->LaunchCharacter(LaunchVector, false, true);
	}
}

void UMDJParkourMovementComponent::WallRunUpdateEvent()
{
	if (!bWallRunSuppressed)
	{
		WallRunUpdate();
	}
}

void UMDJParkourMovementComponent::ResetWallRunSuppresstion()
{
	GetWorld()->GetTimerManager().ClearTimer(FTResetWallRunSuppresstion);
	bWallRunSuppressed = false;
}

void UMDJParkourMovementComponent::WallRunEndVectors(FVector& OutRight, FVector& OutLeft)
{
	FVector StartLocation = Character->GetActorLocation();
	FVector RightDir = Character->GetActorRightVector();
	FVector ForwardDir = Character->GetActorForwardVector();

	OutRight = StartLocation + (RightDir * 75.0f) + (ForwardDir * -35.0f);
	OutLeft = StartLocation + (RightDir * -75.0f) + (ForwardDir * -35.0f);
}

bool UMDJParkourMovementComponent::ValidWallRunVector(const FVector InVector)
{
	return FMath::IsWithinInclusive(InVector.Z, -0.52f, 0.52f);
}

FVector UMDJParkourMovementComponent::PlayerToWallVector()
{
	FVector WallAttractionVector = Character->GetActorLocation() - WallRunNormal;
	WallAttractionVector = WallRunNormal * WallAttractionVector.Length();
	return WallAttractionVector;
}


// ------------ Dash ------------
void UMDJParkourMovementComponent::Dash()
{
	if (CharacterMovementComponent && bCanDash && !bIsDashing && Character->GetVelocity().Length() >= 10)
	{
		UE_LOG(ParkourMovementComponent, Warning, TEXT("Dashing"));

		float NewDashStrength = CharacterMovementComponent->IsFalling() ? DashStrength * 0.3f : DashStrength;

		FVector DashInput = Character->GetLastMovementInputVector();

		if (DashInput.IsNearlyZero())
			DashInput = Character->GetActorForwardVector();

		DashInput.Z = 0;
		DashInput.Normalize();

		FVector DashVelocity = DashInput * NewDashStrength;
		DashVelocity = DashVelocity.GetClampedToMaxSize(NewDashStrength);

		bIsDashing = true;
		Character->LaunchCharacter(DashVelocity, true, false);

		ReloadDash();
	}
}


void UMDJParkourMovementComponent::ReloadDash()
{
	FTimerHandle Temp;
	GetWorld()->GetTimerManager().SetTimer(Temp, this, &UMDJParkourMovementComponent::ReloadingDash, DashTimeReload,
	                                       false);
}

void UMDJParkourMovementComponent::ReloadingDash()
{
	bIsDashing = false;
}

// ------------ Slide ------------
void UMDJParkourMovementComponent::InitializeSlide()
{
	if (bCanSlide)
	{
		UE_LOG(ParkourMovementComponent, Log, TEXT("Initialize slide"));
		NormalSpeed = CharacterMovementComponent->MaxWalkSpeed;
		NormalFriction = CharacterMovementComponent->GroundFriction;
		NormalDeceleration = CharacterMovementComponent->BrakingDecelerationWalking;
		NormalCapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SlideCapsuleHalfHeight = NormalCapsuleHalfHeight / 2;
	}
}

void UMDJParkourMovementComponent::Slide()
{
	if (CharacterMovementComponent && !bIsSliding && !CharacterMovementComponent->IsFalling() && bCanSlide && Character
		->GetVelocity().Length() >= 10)
	{
		UE_LOG(ParkourMovementComponent, Warning, TEXT("Sliding"));
		bIsSliding = true;
		StartSlide();
	}
}

void UMDJParkourMovementComponent::StartSlide()
{
	CharacterMovementComponent->MaxWalkSpeed = SlideSpeed;
	CharacterMovementComponent->GroundFriction = SlideFriction;
	CharacterMovementComponent->BrakingDecelerationWalking = SlideDeceleration;
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(SlideCapsuleHalfHeight);

	FVector LaunchVelocity = Character->GetLastMovementInputVector() * SlideSpeed;
	Character->LaunchCharacter(LaunchVelocity, false, false);

	FTimerHandle Temp;
	GetWorld()->GetTimerManager().SetTimer(Temp, this, &UMDJParkourMovementComponent::StopSlide, SlideDuration,
	                                       false);
	OnSlidding.Broadcast();
	// if (bSlideHasBuff)
	// {
	// 	UMDJGhostSlide* GhostSlide = NewObject<UMDJGhostSlide>(this, UMDJGhostSlide::StaticClass());
	// 	if (GhostSlide)
	// 	{
	// 		GhostSlide->UseGhostSlide();
	// 	}
	// }
}

void UMDJParkourMovementComponent::StopSlide()
{
	CharacterMovementComponent->MaxWalkSpeed = NormalSpeed;
	CharacterMovementComponent->GroundFriction = NormalFriction;
	CharacterMovementComponent->BrakingDecelerationWalking = NormalDeceleration;
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(NormalCapsuleHalfHeight);
	bIsSliding = false;

	// if (bSlideHasBuff)
	// {
	// 	
	// }
}

// ------------ Jump ------------
void UMDJParkourMovementComponent::InitializeJump()
{
	if (bCanJump)
	{
		CharacterMovementComponent->JumpZVelocity = JumpZVelocity;
	}
}

void UMDJParkourMovementComponent::StartJump()
{
	if (bCanJump)
	{
		UE_LOG(ParkourMovementComponent, Warning, TEXT("Jump"));
		Character->Jump();
		JumpEvent();
		bIsJumping = true;
	}
}

void UMDJParkourMovementComponent::StopJump()
{
	if (bCanJump)
	{
		Character->StopJumping();
		bIsJumping = false;
	}
}
