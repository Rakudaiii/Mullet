#include "Components/MDJBuffManager.h"

#include "GameFramework/Character.h"
#include "Algo/RandomShuffle.h"
#include "Effect/MDJEffect.h"
#include "Effect/MDJEffectBase.h"
#include "Effect/Effects/Guns/MDJGunBase.h"


UMDJBuffManager::UMDJBuffManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMDJBuffManager::BeginPlay()
{
	Super::BeginPlay();


	Initialize();
}

void UMDJBuffManager::Initialize()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


void UMDJBuffManager::ApplyEffect(TSubclassOf<UMDJEffect> Effect)
{
	if (!Effect) return;
	
	UMDJEffectBase* NewEffect = NewObject<UMDJEffectBase>(this, Effect);
	if (!NewEffect) return;
	
	NewEffect->BaseInitialize(OwnerCharacter);
	NewEffect->ApplyEffect();

	if (!NewEffect->IsA(UMDJGunBase::StaticClass()))
	{
		ActiveEffects.Add(NewEffect);
		RemoveEffect(Effect);
	}
}

void UMDJBuffManager::RemoveEffect(TSubclassOf<UMDJEffect> Effect)
{
	if (!AllEffects.IsEmpty())
	{
		AllEffects.Remove(Effect);
	}
}


void UMDJBuffManager::ShuffleEffets()
{
	if (!AllEffects.IsEmpty())
	{
		Algo::RandomShuffle(AllEffects);
	}
}
