#include "Actors/Traps/MDJElectricTrap.h"

#include "Components/BoxComponent.h"
#include "Components/MDJHealthComponent.h"
#include "Core/Character/MDJMainCharacter.h"


AMDJElectricTrap::AMDJElectricTrap()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetHiddenInGame(false);
	BoxCollision->ShapeColor = FColor::Blue;
}

void AMDJElectricTrap::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle temp;
	GetWorld()->GetTimerManager().SetTimer(temp, this, &AMDJElectricTrap::UseElectricTrap, TickTime, true);
}

void AMDJElectricTrap::UseElectricTrap()
{
	TArray<AActor*> OverlappingActors;
	BoxCollision->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.IsEmpty()) return;

	for (AActor* Actor : OverlappingActors)
	{
		if (AMDJMainCharacter* MainCharacter = Cast<AMDJMainCharacter>(Actor))
		{
			MainCharacter->HealthComponent->TakeDamage(ElectricTrapDamge);
		}
	}
}
