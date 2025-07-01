#include "Effect/Effects/Guns/MDJGunBase.h"
#include "Components/MDJFightSystemComponent.h"
#include "Effect/Effects/Guns/MDJBullet.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY(Gun);

UMDJGunBase::UMDJGunBase()
{
	BulletClass = AMDJBullet::StaticClass();
}

void UMDJGunBase::ApplyEffect()
{
	Super::ApplyEffect();

	if (UMDJFightSystemComponent* FightSystem = Character->FindComponentByClass<UMDJFightSystemComponent>())
	{
		FightSystem->EquipGun(GunClass);
	}
}

void UMDJGunBase::Init(ACharacter* InCharacter)
{
	OwnerCharacterGun = InCharacter;
}

void UMDJGunBase::StartFiring()
{
	if (CurrentAmmo > 0 || (bIsShotGun && bIsReloading))
	{
		Fire();

		if (bIsAuto)
		{
			GetWorld()->GetTimerManager().SetTimer(AutoFireHandle, this, &UMDJGunBase::Fire, FireRate, true);
		}
	}
	else
	{
		ReloadAmmo(false);
	}
}

void UMDJGunBase::StopFiring()
{
	if (bIsAuto)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);
	}
}

void UMDJGunBase::Fire()
{
	if (bIsReloading && bIsShotGun)
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadHandle);
		bIsReloading = false;
		bIsManualReloading = false;
	}

	if (CurrentAmmo <= 0)
	{
		ReloadAmmo(false);
		return;
	}

	--CurrentAmmo;

	if (!OwnerCharacterGun || !BulletClass)
		return;

	const FVector MuzzleLocation = OwnerCharacterGun->GetActorLocation() + OwnerCharacterGun->GetActorForwardVector() * 100.0f;
	const FRotator MuzzleRotation = OwnerCharacterGun->GetControlRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerCharacterGun;
	SpawnParams.Instigator = OwnerCharacterGun->GetInstigator();

	GetWorld()->SpawnActor<AMDJBullet>(BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams);

	if (CurrentAmmo <= 0)
	{
		ReloadAmmo(false);
	}
}

void UMDJGunBase::ReloadAmmo(bool bManual)
{
	if (bIsReloading || CurrentAmmo >= MaxAmmo)
		return;

	bIsReloading = true;
	bIsManualReloading = bManual;

	GetWorld()->GetTimerManager().SetTimer(
		ReloadHandle,
		this,
		&UMDJGunBase::CompleteReload,
		ReloadTime,
		false
	);

	const FString Mode = bIsShotGun ? TEXT("Shotgun") : TEXT("Normal");
	UE_LOG(Gun, Log, TEXT("Started %s reload..."), *Mode);
}

void UMDJGunBase::CompleteReload()
{
	if (bIsShotGun)
	{
		CurrentAmmo = FMath::Clamp(CurrentAmmo + 1, 0, MaxAmmo);
		UE_LOG(Gun, Log, TEXT("Shotgun: Loaded one shell. Ammo: %d"), CurrentAmmo);

		const bool bContinueReloading = CurrentAmmo < MaxAmmo;

		if (bContinueReloading)
		{
			GetWorld()->GetTimerManager().SetTimer(
				ReloadHandle,
				this,
				&UMDJGunBase::CompleteReload,
				ReloadTime,
				false
			);
		}
		else
		{
			bIsReloading = false;
			bIsManualReloading = false;
			UE_LOG(Gun, Log, TEXT("Shotgun: Reload complete."));
		}
	}
	else
	{
		CurrentAmmo = MaxAmmo;
		bIsReloading = false;
		UE_LOG(Gun, Log, TEXT("Reload complete."));
	}
}
