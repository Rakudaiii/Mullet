#include "AI/MDJEnemy.h"

#include "AI/MDJAIController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MDJFightSystemComponent.h"
#include "Components/MDJHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMDJEnemy::AMDJEnemy()
{
	PrimaryActorTick.bCanEverTick = true;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 90.0f,0.0f));

	HealthComponent = CreateDefaultSubobject<UMDJHealthComponent>(TEXT("HealthComponent"));
	FightSystemComponent = CreateDefaultSubobject<UMDJFightSystemComponent>(TEXT("FightSystemComponent"));

	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	AIControllerClass = AMDJAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
}

void AMDJEnemy::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->Initialize(Health);

	HealthComponent->OnDead.AddDynamic(this, &AMDJEnemy::OnDead);
}

void AMDJEnemy::OnDead()
{
	SetActorLocation(FVector(0.0f, 0.0f, -1000.0f));

	ACharacter* CharacterKiller = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (UMDJHealthComponent* CharacterKillerHealthComponent = CharacterKiller->FindComponentByClass<UMDJHealthComponent>())
	{
		CharacterKillerHealthComponent->GainHealth(2.0f);
	}
	
	FTimerHandle temp;
	GetWorld()->GetTimerManager().SetTimer(temp, this, &AMDJEnemy::DestroySelf, 1.0f, false);
}

void AMDJEnemy::DestroySelf()
{
	Destroy();
}

void AMDJEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
