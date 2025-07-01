#include "MulletMadJack/Public/Components/MDJFightSystemComponent.h"

#include "Camera/CameraComponent.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"
#include "Components/CapsuleComponent.h"
#include "Components/MDJHealthComponent.h"
#include "Core/Character/MDJMainCharacter.h"
#include "Effect/Effects/Guns/Pistols/MDJGlock.h"
#include "GameFramework/Character.h"

//Log
DEFINE_LOG_CATEGORY(FightSystemComponent);

UMDJFightSystemComponent::UMDJFightSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMDJFightSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}


void UMDJFightSystemComponent::Initialize()
{
	Character = Cast<ACharacter>(GetOwner());

	EquipGun(UMDJGlock::StaticClass());
}


// ------------ Shoot ------------
void UMDJFightSystemComponent::EquipGun(TSubclassOf<UMDJGunBase> GunClass)
{
	if (!GunClass) return;

	CurrentGun = NewObject<UMDJGunBase>(this, GunClass);
	
	UE_LOG(FightSystemComponent, Warning, TEXT("Current gun is:%s"), *CurrentGun->GetName());

	CurrentGun->Init(Character);
}

void UMDJFightSystemComponent::StartFiring()
{
	if (!CurrentGun || !bCanShoot) return;

	CurrentGun->StartFiring();
}

void UMDJFightSystemComponent::StopFiring()
{
	if (!CurrentGun) return;

	CurrentGun->StopFiring();
}

void UMDJFightSystemComponent::ReloadGun()
{
	CurrentGun->ReloadAmmo(false);
}




