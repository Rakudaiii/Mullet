#include "Effect/Effects/Buffs/MDJJumpEMP.h"

#include "Components/MDJFightSystemComponent.h"
#include "Core/Character/MDJMainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void UMDJJumpEMP::ApplyEffect()
{
	Super::ApplyEffect();


	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("JumpEMP was activated"));
		MainCharacter->OnCharacterLanded.AddDynamic(this, &UMDJJumpEMP::UseJumpEMP);
	}
	else
	{
		UE_LOG(Effects, Error, TEXT("JumpEMP wasn't activated"));
	}
}

void UMDJJumpEMP::UseJumpEMP()
{
	if (FMath::RandRange(0, 99) >= GetChance())
		return;

	float FallSpeed = -MainCharacter->GetCharacterMovement()->Velocity.Z;
	float JumpZ = MainCharacter->GetCharacterMovement()->JumpZVelocity;
	float MinHardLandingSpeed = JumpZ * 0.8f;

	if (FallSpeed <= MinHardLandingSpeed)
		return;

	UE_LOG(Effects, Warning, TEXT("Use Jump EMP"));

	const FVector Start = MainCharacter->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MainCharacter);

	TArray<AActor*> HitActors;
	bool bHit = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		Start,
		GetRadius(),
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		HitActors
	);

	if (bHit)
	{
		OutActors = HitActors;

		for (AActor* HitActor : HitActors)
		{
			if (!HitActor) continue;

			if (UMDJFightSystemComponent* FightSystem = HitActor->FindComponentByClass<UMDJFightSystemComponent>())
			{
				UE_LOG(Effects, Warning, TEXT("Disarmed Actor: %s"), *HitActor->GetName());
				FightSystem->SetbCanShoot(false);
			}
		}

		StartResetDebuff();
	}

	DrawDebugShockPulse(Start);
}

void UMDJJumpEMP::StartResetDebuff()
{
	FTimerHandle ResetTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &UMDJJumpEMP::ResetDebuff, GetResetTime(), false);
}

void UMDJJumpEMP::ResetDebuff()
{
	for (AActor* Actor : OutActors)
	{
		if (!Actor) continue;

		if (UMDJFightSystemComponent* FightSystem = Actor->FindComponentByClass<UMDJFightSystemComponent>())
		{
			UE_LOG(Effects, Warning, TEXT("Reset disarm for: %s"), *Actor->GetName());
			FightSystem->SetbCanShoot(true);
		}
	}

	OutActors.Empty();
}

void UMDJJumpEMP::DrawDebugShockPulse(const FVector Start)
{
	if (GetbDrawDebug() && !GetRemoveAllDebug())
	{
		DrawDebugCircle(
			GetWorld(),
			Start + FVector(0.f, 0.f, GetZOffset()),
			GetRadius(),
			GetSegments(),
			GetColor(),
			false,
			GetLifeTime(),
			0,
			GetThickness(),
			FVector(1, 0, 0),
			FVector(0, 1, 0),
			false
		);
	}
}
