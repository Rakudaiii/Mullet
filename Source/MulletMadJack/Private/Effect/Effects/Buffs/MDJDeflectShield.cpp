#include "Effect/Effects/Buffs/MDJDeflectShield.h"

#include "Components/MDJHealthComponent.h"
#include "Core/Character/MDJMainCharacter.h"

void UMDJDeflectShield::ApplyEffect()
{
	Super::ApplyEffect();

	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("Deflect Shield was activated"));
		Time = FMath::RandRange(GetMinChance(), GetMaxChance());
		GetWorld()->GetTimerManager().SetTimer(DeflectShieldTimerHandle, this, &UMDJDeflectShield::StartTimer, 1.0f,
		                                       true);
	}
	else
	{
		UE_LOG(Effects, Log, TEXT("Deflect Shield wasn't activated"));
	}
}

void UMDJDeflectShield::StartTimer()
{
	PastTime += 1.0f;
	if (PastTime >= Time)
	{
		UE_LOG(Effects, Warning, TEXT("Deflect Shield was used"));
		MainCharacter->HealthComponent->EnableGodMode("DeflectShield", GetDurationTime());
		PastTime = 0;
		Time = FMath::RandRange(GetMinChance(), GetMaxChance());
	}
	/*else
	{
		UE_LOG(Effects, Log, TEXT("Time:%f"), Time);
		UE_LOG(Effects, Log, TEXT("PastTime:%f"), PastTime);
	}*/
}
