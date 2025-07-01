#include "Effect/Effects/Guns/Submachine/MDJMp5k.h"



UMDJMp5k::UMDJMp5k()
{
	GunClass = UMDJMp5k::StaticClass();
	
	MaxAmmo = 30.0f;
	CurrentAmmo = MaxAmmo;
	GunDamage = 1.0f;
	bUseProjectile = false;
	FireRate = 0.1f;
	bIsAuto = true;
	ReloadTime = 3.0f;
}
