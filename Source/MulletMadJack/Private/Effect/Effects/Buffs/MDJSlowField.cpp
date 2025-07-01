#include "Effect/Effects/Buffs/MDJSlowField.h"

#include "Core/Character/MDJMainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UMDJSlowField::ApplyEffect()
{
	Super::ApplyEffect();

	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("SlowField was activated"));
		GetWorld()->GetTimerManager().SetTimer(SlowFieldTimerHandle, this, &UMDJSlowField::UseSlowField, 0.1f, true);
	}
	else
	{
		UE_LOG(Effects, Log, TEXT("SlowField wasn't activated"));
	}
}



void UMDJSlowField::UseSlowField()
{

	FVector Start = MainCharacter->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MainCharacter);

	TArray<AActor*> OutActors;
	bool bHit = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		Start,
		GetRadius(),
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		OutActors
	);

	//All Enemies in radius  
	TSet<ACharacter*> CurrentHits;

	if (bHit)
	{
		for (AActor* HitActor : OutActors)
		{
			if (ACharacter* HitCharacter = Cast<ACharacter>(HitActor))
			{
				CurrentHits.Add(HitCharacter);

				// If we haven't slowed this character down yet
				if (!OriginalSpeeds.Contains(HitCharacter))
				{
					float BaseSpeed = HitCharacter->GetCharacterMovement()->MaxWalkSpeed;
					OriginalSpeeds.Add(HitCharacter, BaseSpeed);
					
					float NewSpeed = FMath::Clamp(BaseSpeed - GetSpeedDecrease(), 100.f, BaseSpeed); 
					HitCharacter->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;

					UE_LOG(Effects, Log, TEXT("Slow: %s (%.1f → %.1f)"), *HitCharacter->GetName(), BaseSpeed, NewSpeed);
				}
			}
		}
	}

	//Enemies come out from radius - reset speed
	TArray<ACharacter*> CharactersToRemove;
	for (auto& Elem : OriginalSpeeds)
	{
		ACharacter* AffectedChar = Elem.Key;

		if (!CurrentHits.Contains(AffectedChar)) // Come out from zone
		{
			float OriginalSpeed = Elem.Value;

			if (IsValid(AffectedChar))
			{
				AffectedChar->GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;
				UE_LOG(Effects, Log, TEXT("Reset speed for: %s"), *AffectedChar->GetName());
			}

			CharactersToRemove.Add(AffectedChar);
		}
	}

	// We remove those who are no longer slowed down
	for (ACharacter* Char : CharactersToRemove)
	{
		OriginalSpeeds.Remove(Char);
	}

	DrawDebugSlowField(Start);
}




void UMDJSlowField::DrawDebugSlowField(const FVector Start) 
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
			0.1f,
			0,
			GetThickness(),
			FVector(1, 0, 0),
			FVector(0, 1, 0),
			false
		);
	}
}
