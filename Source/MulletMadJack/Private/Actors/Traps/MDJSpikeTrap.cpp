#include "Actors/Traps/MDJSpikeTrap.h"

#include "Components/BoxComponent.h"
#include "Components/MDJHealthComponent.h"
#include "Core/Character/MDJMainCharacter.h"



AMDJSpikeTrap::AMDJSpikeTrap()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spikes_SM"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

void AMDJSpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMDJSpikeTrap::HpDecrease);
}

void AMDJSpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	float Offset = FMath::Sin(RunningTime * Speed) * Amplitude;

	FVector WorldMoveDirection = GetActorTransform().TransformVector(MoveDirection.GetSafeNormal());

	FVector NewLocation = StartLocation + WorldMoveDirection * Offset;

	SetActorLocation(NewLocation);
}

void AMDJSpikeTrap::HpDecrease(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			 const FHitResult& SweepResult)
{
	if (AMDJMainCharacter* MainCharacter = Cast<AMDJMainCharacter>(OtherActor))
	{
		MainCharacter->HealthComponent->TakeDamage(SpikeDamage);
	}
}
