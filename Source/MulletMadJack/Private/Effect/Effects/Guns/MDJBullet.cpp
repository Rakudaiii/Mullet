#include "Effect/Effects/Guns/MDJBullet.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/MDJFightSystemComponent.h"
#include "Components/MDJHealthComponent.h"
#include "Effect/Effects/Guns/MDJGunBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"


AMDJBullet::AMDJBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletStaticMesh"));
	BulletStaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	RootComponent = BulletStaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(BulletStaticMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}


void AMDJBullet::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(Gun, Warning, TEXT("Hello im bullet, i was spawned"))

	Initialize();

	if (!bUseProjectile)
	{
		if (!bIsShotGun)
		{
			UseSingleTrace();
		}
		else
		{
			UseMiltyTrace();
		}

		Destroy();
	}
	else
	{
		UseProjectile();
	}
}

void AMDJBullet::UseSingleTrace()
{
	UCameraComponent* Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();
	if (!Camera) return;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * 10000.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);


	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	example(bHit, Hit, Start, End);
}

void AMDJBullet::UseMiltyTrace()
{
	AController* Controller = Owner->GetInstigatorController();
	if (!Controller) return;

	FVector EyeLocation;
	FRotator EyeRotation;
	Controller->GetPlayerViewPoint(EyeLocation, EyeRotation);

	for (int32 i = 0; i < Pellets; ++i)
	{
		// Генерация случайного направления с разбросом
		FRotator RandomRot = EyeRotation;
		RandomRot.Yaw += FMath::RandRange(-SpreadAngle, SpreadAngle);
		RandomRot.Pitch += FMath::RandRange(-SpreadAngle, SpreadAngle);

		FVector ShotDirection = RandomRot.Vector();
		FVector TraceEnd = EyeLocation + ShotDirection * MaxRange;

		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Owner);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			EyeLocation,
			TraceEnd,
			ECC_Visibility,
			Params
		);
		example(bHit, Hit, EyeLocation, TraceEnd);
	}
}

void AMDJBullet::UseProjectile()
{
}

void AMDJBullet::example(const bool bHit, const FHitResult Hit, const FVector Start, const FVector End)
{
	if (bHit)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor) return;

		APawn* HitPawn = Cast<APawn>(HitActor);
		APawn* ShooterPawn = Cast<APawn>(OwnerCharacter);

		bool bShooterIsAI = ShooterPawn && !ShooterPawn->IsPlayerControlled();
		bool bTargetIsAI = HitPawn && !HitPawn->IsPlayerControlled();

		//If hit the same Controller
		if (bShooterIsAI && bTargetIsAI)
			return;

		if (UMDJHealthComponent* HitActorHealthComponent = HitActor->FindComponentByClass<UMDJHealthComponent>())
		{
			UE_LOG(FightSystemComponent, Warning, TEXT("HitBoneName:%s"), *Hit.BoneName.ToString())
			if (Hit.BoneName == "head" || Hit.BoneName == "Head")
			{
				HitActorHealthComponent->TakeDamage(Damage * 2, OwnerCharacter);
			}
			else
			{
				HitActorHealthComponent->TakeDamage(Damage, OwnerCharacter);
			}
			//OnFire.Broadcast(HitActor);
			OwnerCharacter->FindComponentByClass<UMDJFightSystemComponent>()->OnFire.Broadcast(HitActor);
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
}

void AMDJBullet::Initialize()
{
	UMDJGunBase* CurrentGunInfo = Cast<UMDJGunBase>(
		GetOwner()->FindComponentByClass<UMDJFightSystemComponent>()->GetCurrentGun());
	OwnerCharacter = CurrentGunInfo->GetOwnerCharacter();

	bUseProjectile = CurrentGunInfo->GetUseProjectile();
	Damage = CurrentGunInfo->GetGunDamage();

	bIsShotGun = CurrentGunInfo->GetIsShotGun();
	Pellets = CurrentGunInfo->GetPellets();
	MaxRange = CurrentGunInfo->GetMaxRange();
	SpreadAngle = CurrentGunInfo->GetSpreadAngle();
}
