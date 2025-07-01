#include "Effect/Effects/Guns//Pistols/MDJGlock.h"


UMDJGlock::UMDJGlock()
{
	GunClass = UMDJGlock::StaticClass();

	MaxAmmo = 10.0f;
	CurrentAmmo = MaxAmmo;
	GunDamage = 1.0f;
	bUseProjectile = false;
	FireRate = 0.5f;
	bIsAuto = false;
	ReloadTime = 3.0f;
}
