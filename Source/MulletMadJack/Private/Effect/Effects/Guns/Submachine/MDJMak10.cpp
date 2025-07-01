#include "Effect/Effects/Guns/Submachine/MDJMak10.h"




UMDJMak10::UMDJMak10()
{
	GunClass = UMDJMak10::StaticClass();
	
	MaxAmmo = 20.0f;
	CurrentAmmo = MaxAmmo;
	GunDamage = 1.0f;
	bUseProjectile = false;
	FireRate = 0.2f;
	bIsAuto = true;
	ReloadTime = 3.0f;
}
