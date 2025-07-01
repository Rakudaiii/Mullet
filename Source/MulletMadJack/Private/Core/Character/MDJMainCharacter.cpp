#include "Core/Character/MDJMainCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/MDJBuffManager.h"
#include "Components/MDJFightSystemComponent.h"
#include "Components/MDJHealthComponent.h"
#include "Components/MDJParkourMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMDJMainCharacter::AMDJMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 90.0f,0.0f));
	Camera->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = true;


	//SetupComponents
	FightSystemComponent = CreateDefaultSubobject<UMDJFightSystemComponent>(TEXT("FightSystemComponent"));
	HealthComponent = CreateDefaultSubobject<UMDJHealthComponent>(TEXT("HealthComponent"));
	ParkourMovementComponent = CreateDefaultSubobject<UMDJParkourMovementComponent>(TEXT("ParkourMovementComponent"));
	BuffManager = CreateDefaultSubobject<UMDJBuffManager>(TEXT("BuffManager"));
}


void AMDJMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeComponets();

	HealthComponent->OnDead.AddDynamic(this, &AMDJMainCharacter::OnDead);
}

void AMDJMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	OnCharacterLanded.Broadcast();

	ParkourMovementComponent->LandEvent();
}

void AMDJMainCharacter::OnDead()
{
	ULevel* CurrentLevel = GetWorld()->GetCurrentLevel();
	FName CurrentStreamingLevelName = CurrentLevel->GetOutermost()->GetFName();

	UGameplayStatics::OpenLevel(this, CurrentStreamingLevelName);
}


void AMDJMainCharacter::InitializeComponets()
{
	HealthComponent->Initialize(Health);
}


void AMDJMainCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMDJMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Key is Space - Event Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, ParkourMovementComponent,
		                                   &UMDJParkourMovementComponent::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, ParkourMovementComponent,
		                                   &UMDJParkourMovementComponent::StopJump);

		//Key is Left Shift - Event Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, ParkourMovementComponent,
		                                   &UMDJParkourMovementComponent::Dash);

		//Key is C - Event Slide
		EnhancedInputComponent->BindAction(SlideAction, ETriggerEvent::Started, ParkourMovementComponent,
		                                   &UMDJParkourMovementComponent::Slide);

		//Key is Left mouse button - Event Shoot
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, FightSystemComponent,
									   &UMDJFightSystemComponent::StartFiring);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, FightSystemComponent,
									   &UMDJFightSystemComponent::StopFiring);

		//Key is R - Reload Ammo
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, FightSystemComponent,
									   &UMDJFightSystemComponent::ReloadGun);

		//Keys WASD - Event Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMDJMainCharacter::Move);

		//Mouse X&Y - Event Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMDJMainCharacter::Look);
	}
}

void AMDJMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMDJMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
