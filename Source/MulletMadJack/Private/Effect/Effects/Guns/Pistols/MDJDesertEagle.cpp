#include "Effect/Effects/Guns/Pistols/MDJDesertEagle.h"




UMDJDesertEagle::UMDJDesertEagle()
{
	GunClass = UMDJDesertEagle::StaticClass();

	MaxAmmo = 7.0f;
	CurrentAmmo = MaxAmmo;
	GunDamage = 1.0f;
	bUseProjectile = false;
	FireRate = 0.5f;
	bIsAuto = false;
	ReloadTime = 5.0f;
}
