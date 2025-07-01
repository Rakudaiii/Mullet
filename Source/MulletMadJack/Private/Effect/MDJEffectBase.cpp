#include "MulletMadJack/Public/Effect/MDJEffectBase.h"

#include "Core/Character/MDJMainCharacter.h"


DEFINE_LOG_CATEGORY(Effects);

UMDJEffectBase::UMDJEffectBase()
{
	static ConstructorHelpers::FObjectFinder<UMDJEffectsDataAsset> EffectDataObj(TEXT("/Game/MulletMadJack/BluePrints/Effects/DataAssets/DA_Effects.DA_Effects"));

	if (EffectDataObj.Succeeded())
	{
		EffectsDataAsset = EffectDataObj.Object;
		UE_LOG(LogTemp, Log, TEXT("Successfully loaded DA_Effects."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DA_Effects! Check the path."));
	}
}

void UMDJEffectBase::BaseInitialize(AActor* Actor)
{
	MainCharacter = Cast<AMDJMainCharacter>(Actor);
	Character = Cast<ACharacter>(Actor);

	
}


void UMDJEffectBase::ApplyEffect()
{
	
}
