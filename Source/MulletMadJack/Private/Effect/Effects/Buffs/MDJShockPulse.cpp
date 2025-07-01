#include "Effect/Effects/Buffs/MDJShockPulse.h"

#include "Components/MDJHealthComponent.h"
#include "Core/Character/MDJMainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"


void UMDJShockPulse::ApplyEffect()
{
	Super::ApplyEffect();

	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("ShockPulse was activated"));
		MainCharacter->HealthComponent->OnTakeDamage.AddDynamic(this, &UMDJShockPulse::UseShockPulse);
	}
	else
	{
		UE_LOG(Effects, Error, TEXT("Error"));
	}
}


void UMDJShockPulse::UseShockPulse(AActor* DamagedActor)
{
	if (FMath::RandRange(0, 99) >= GetChance())
		return;

	FVector Start = MainCharacter->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MainCharacter);


	TArray<AActor*> OutActors;
	bool bHit = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		Start,
		GetRadius(),
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		OutActors
	);

	if (bHit)
	{
		for (const AActor* HitActor : OutActors)
		{
			if (!HitActor) continue;

			if (UMDJHealthComponent* HitActorHealthComponent = HitActor->FindComponentByClass<UMDJHealthComponent>())
			{
				HitActorHealthComponent->TakeDamage(GetShockPulseDamage(), MainCharacter);
			}
		}
		UE_LOG(Effects, Warning, TEXT("ShockPulse was used"));
	}
	DrawDebugShockPulse(Start);
}

void UMDJShockPulse::DrawDebugShockPulse(const FVector Start)
{
	if (GetbDrawDebug() && !GetRemoveAllDebug())
	{
		DrawDebugSphere(
			GetWorld(),
			Start,
			GetRadius(),
			GetSegments(),
			GetColor(),
			false,
			GetLifeTime()
		);
	}
}
