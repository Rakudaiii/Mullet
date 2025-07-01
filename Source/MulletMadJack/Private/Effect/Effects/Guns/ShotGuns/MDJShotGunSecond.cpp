#include "Effect/Effects/Guns/ShotGuns/MDJShotGunSecond.h"

UMDJShotGunSecond::UMDJShotGunSecond()
{
	GunClass = UMDJShotGunSecond::StaticClass();
	
	MaxAmmo = 10.0f;
	CurrentAmmo = MaxAmmo;
	GunDamage = 1.0f;
	FireRate = 0.7f;
	bIsAuto = true;
	ReloadTime = 0.5f;

	bIsShotGun = true;
	Pellets = 10.0f;
	MaxRange = 2000.0f;
	SpreadAngle = 5.0f;
}
