#include "Effect/Effects/Guns/ShotGuns/MDJShotGunFirst.h"

UMDJShotGunFirst::UMDJShotGunFirst()
{
	GunClass = UMDJShotGunFirst::StaticClass();
	
	MaxAmmo = 7.0f;
	CurrentAmmo = MaxAmmo;
	GunDamage = 1.0f;
	FireRate = 1.0f;
	bIsAuto = false;
	ReloadTime = 0.5f;

	bIsShotGun = true;
	Pellets = 10.0f;
	MaxRange = 2000.0f;
	SpreadAngle = 5.0f;
}
