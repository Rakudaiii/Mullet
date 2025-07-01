#include "Effect/Effects/Buffs/MDJReflectShot.h"

#include "Components/MDJFightSystemComponent.h"
#include "Components/MDJHealthComponent.h"
#include "Core/Character/MDJMainCharacter.h"
#include "Effect/Effects/Guns/MDJGunBase.h"


void UMDJReflectShot::ApplyEffect()
{
	Super::ApplyEffect();

	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("Reflect Shot was activated"));
		MainCharacter->HealthComponent->OnTakeDamage.AddDynamic(this, &UMDJReflectShot::UseReflectShot);
	}
	else
	{
		UE_LOG(Effects, Error, TEXT("Reflect Shot wasn't activated"));
	}
}

void UMDJReflectShot::UseReflectShot(AActor* DamagedActor)
{
	if (FMath::RandRange(0, 99) >= GetChance())
		return;

	if (!DamagedActor)
		return;
	
	MainCharacter->HealthComponent->EnableGodMode("ReflectShot", 0.1f);

	if (UMDJFightSystemComponent* DamagedActorFightSystemComponent = DamagedActor->FindComponentByClass<
		UMDJFightSystemComponent>())
	{
		if (UMDJHealthComponent* DamagedActorHealthComponent = DamagedActor->FindComponentByClass<
			UMDJHealthComponent>())
		{
			DamagedActorHealthComponent->
				TakeDamage(DamagedActorFightSystemComponent->GetCurrentGun()->GetGunDamage(), MainCharacter);
		}
	}
}
