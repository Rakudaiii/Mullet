#include "Effect/Effects/Buffs/MDJKillShield.h"

#include "Components/MDJFightSystemComponent.h"
#include "Components/MDJHealthComponent.h"
#include "Core/Character/MDJMainCharacter.h"


void UMDJKillShield::ApplyEffect()
{
	Super::ApplyEffect();

	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("KillShield was activated"));
		MainCharacter->FightSystemComponent->OnFire.AddDynamic(this, &UMDJKillShield::UseKillShield);
	}
	else
	{
		UE_LOG(Effects, Error, TEXT("OnKillShield wasn't activated"));
	}
}



void UMDJKillShield::UseKillShield(AActor* HitActor)
{
	if (UMDJHealthComponent* HitActorHealthComponent = HitActor->FindComponentByClass<UMDJHealthComponent>())
	{
		if (HitActorHealthComponent->IsDead(HitActorHealthComponent->GetCurrentHealth()))
		{
			UE_LOG(Effects, Log, TEXT("KillShield was used"));
			MainCharacter->HealthComponent->EnableGodMode("KillShield", GetResetTime(), GetChance());
		}
	}
}
