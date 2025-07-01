#include "Effect/Effects/Buffs/MDJBerserkMode.h"

#include "Components/MDJHealthComponent.h"
#include "Components/MDJParkourMovementComponent.h"
#include "Core/Character/MDJMainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/MDJEnemy.h"
#include "Components/MDJFightSystemComponent.h"
#include "Effect/Effects/Guns/MDJGunBase.h"


void UMDJBerserkMode::ApplyEffect()
{
	Super::ApplyEffect();

	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("BerserkMode was activated"))
		GetWorld()->GetTimerManager().SetTimer(BerserkModeTimerHandle, this, &UMDJBerserkMode::CheckHealth, 0.1f,
		                                       true);
	}
	else
	{
		UE_LOG(Effects, Log, TEXT("BerserkMode wasn't activated"))
	}
}

void UMDJBerserkMode::SaveBaseMovementStats()
{
	if (!MainCharacter || !MainCharacter->ParkourMovementComponent || !MainCharacter->FightSystemComponent) return;

	CharacterBaseSpeed = MainCharacter->GetCharacterMovement()->MaxWalkSpeed;
	CharacterBaseDashStrength = MainCharacter->ParkourMovementComponent->GetDashStrength();
	CharacterBaseSlideSpeed = MainCharacter->ParkourMovementComponent->GetSlideSpeed();
	CharacterBaseGunDamage = MainCharacter->FightSystemComponent->GetCurrentGun()->GetGunDamage();
}


void UMDJBerserkMode::CheckHealth()
{
	const float CurrentHealth = MainCharacter->HealthComponent->GetCurrentHealth();

	if (CurrentHealth <= GetTriggerHealth() && !bBerserkModeIsActivated)
	{
		UseBerserkMode();
		bBerserkModeIsActivated = true;
	}

	if (CurrentHealth > GetTriggerHealth() && bBerserkModeIsActivated)
	{
		DeactivateBerserkMode();
		bBerserkModeIsActivated = false;
	}
}

void UMDJBerserkMode::UseBerserkMode()
{
	if (!MainCharacter || !MainCharacter->ParkourMovementComponent) return;

	UE_LOG(Effects, Warning, TEXT("BerserkMode was used"));

	SaveBaseMovementStats();

	MainCharacter->GetCharacterMovement()->MaxWalkSpeed = CharacterBaseSpeed + GetMovementSpeedMultiplier();
	MainCharacter->ParkourMovementComponent->SetDashStrength(CharacterBaseDashStrength + GetDashSpeedMultiplier());
	MainCharacter->ParkourMovementComponent->SetSlideSpeed(CharacterBaseSlideSpeed + GetSlideSpeedMultiplier());
	MainCharacter->FightSystemComponent->GetCurrentGun()->SetGunDamage(CharacterBaseGunDamage + GetGunDamageMultiplier());
	
	DebugLog();

	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMDJEnemy::StaticClass(), Enemies);
	if (!Enemies.IsEmpty())
	{
		for (AActor* Actor : Enemies)
		{
			AMDJEnemy* Enemy = Cast<AMDJEnemy>(Actor);
			if (!Enemy) continue;

			UCharacterMovementComponent* MoveComp = Enemy->GetCharacterMovement();
			if (!MoveComp) continue;

			if (!EnemyOriginalSpeeds.Contains(Enemy))
			{
				EnemyOriginalSpeeds.Add(Enemy, MoveComp->MaxWalkSpeed);
			}

			const float NewSpeed = FMath::Clamp(MoveComp->MaxWalkSpeed - GetSpeedDecrease(), 100.0f,
			                                    MoveComp->MaxWalkSpeed);

			MoveComp->MaxWalkSpeed = NewSpeed;
		}
	}
}

void UMDJBerserkMode::DeactivateBerserkMode()
{
	UE_LOG(Effects, Warning, TEXT("BerserkMode was deactivated"));

	MainCharacter->GetCharacterMovement()->MaxWalkSpeed = CharacterBaseSpeed;
	MainCharacter->ParkourMovementComponent->SetDashStrength(CharacterBaseDashStrength);
	MainCharacter->ParkourMovementComponent->SetSlideSpeed(CharacterBaseSlideSpeed);
	MainCharacter->FightSystemComponent->GetCurrentGun()->SetGunDamage(CharacterBaseGunDamage);
	DebugLog();

	for (const TPair<TWeakObjectPtr<ACharacter>, float>& Pair : EnemyOriginalSpeeds)
	{
		if (!Pair.Key.IsValid()) continue;

		ACharacter* Enemy = Pair.Key.Get();
		if (UCharacterMovementComponent* MoveComp = Enemy->GetCharacterMovement())
		{
			MoveComp->MaxWalkSpeed = Pair.Value;
		}
	}

	EnemyOriginalSpeeds.Empty();
}

void UMDJBerserkMode::DebugLog() const
{
	UE_LOG(Effects, Log, TEXT("Character speed:%f"), MainCharacter->GetCharacterMovement()->MaxWalkSpeed);
	UE_LOG(Effects, Log, TEXT("Character dash strength:%f"),
	       MainCharacter->ParkourMovementComponent->GetDashStrength());
	UE_LOG(Effects, Log, TEXT("Character slide speed:%f"), MainCharacter->ParkourMovementComponent->GetSlideSpeed());
	UE_LOG(Effects, Log, TEXT("Character gun damage:%f"), MainCharacter->FightSystemComponent->GetCurrentGun()->GetGunDamage());
}
