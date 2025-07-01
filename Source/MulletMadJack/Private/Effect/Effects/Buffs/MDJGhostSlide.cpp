#include "Effect/Effects/Buffs/MDJGhostSlide.h"

#include "AI/MDJAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/MDJParkourMovementComponent.h"
#include "Core/Character/MDJMainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"


void UMDJGhostSlide::ApplyEffect()
{
	Super::ApplyEffect();
	if (EffectsDataAsset)
	{
		UE_LOG(Effects, Log, TEXT("GhostSlide was activated"))
		MainCharacter->ParkourMovementComponent->OnSlidding.AddDynamic(this, &UMDJGhostSlide::UseGhostSlide);
	}
	else
	{
		UE_LOG(Effects, Log, TEXT("GhostSlide wasn't activated"))
	}
}

void UMDJGhostSlide::UseGhostSlide()
{
	if (FMath::RandRange(0, 99) >= GetChance())
		return;

	FVector Start = MainCharacter->GetActorLocation();

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
		for (AActor* HitActor : OutActors)
		{
			if (!HitActor) continue;
			
			APawn* AIPawn = Cast<APawn>(HitActor);

			AMDJAIController* AIController = Cast<AMDJAIController>(AIPawn->GetController());

			if (UBlackboardComponent* BB = AIController->GetBlackboardComponent())
			{
				const FName KeyName = "EnumKey";
				
				BB->SetValueAsEnum(KeyName, 0);
			}
		}
	}
	UE_LOG(Effects, Warning, TEXT("GhostSlide was used"));
	DrawDebugGhostSlide(Start);
}

void UMDJGhostSlide::DrawDebugGhostSlide(const FVector Start)
{
	if (GetbDrawDebug() && !GetRemoveAllDebug())
	{
		DrawDebugSphere(
			GetWorld(),
			Start,
			GetRadius(),
			GetSegments(),
			GetColor(),
			false,
			GetLifeTime()
		);
	}
}
