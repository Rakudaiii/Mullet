#include "Effect/Effects/Buffs/MDJAutoAimAssist.h"

#include "Core/Character/MDJMainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


void UMDJAutoAimAssist::ApplyEffect()
{
	Super::ApplyEffect();

	
	GetWorld()->GetTimerManager().SetTimer(
		AutoAimTimerHandle,
		this,
		&UMDJAutoAimAssist::TickAutoAim,
		TickRate,
		true
	);
}

void UMDJAutoAimAssist::TickAutoAim()
{
	AActor* Target = FindClosestTarget();
	if (!Target || !MainCharacter) return;

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
		MainCharacter->GetActorLocation(),
		Target->GetActorLocation()
	);

	// Поворачиваем только yaw (в горизонтальной плоскости)
	FRotator NewControlRot = MainCharacter->GetControlRotation();
	NewControlRot.Yaw = LookAtRot.Yaw;

	if (AController* Controller = MainCharacter->GetController())
	{
		Controller->SetControlRotation(NewControlRot);
	}
}

AActor* UMDJAutoAimAssist::FindClosestTarget()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MainCharacter);

	TArray<AActor*> OutActors;

	bool bHit = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		MainCharacter->GetActorLocation(),
		Radius,
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		OutActors
	);

	if (!bHit || OutActors.Num() == 0)
		return nullptr;

	AActor* Closest = nullptr;
	float MinDistSqr = TNumericLimits<float>::Max();

	for (AActor* Actor : OutActors)
	{
		if (!Actor) continue;

		const float DistSqr = FVector::DistSquared(MainCharacter->GetActorLocation(), Actor->GetActorLocation());
		if (DistSqr < MinDistSqr)
		{
			MinDistSqr = DistSqr;
			Closest = Actor;
		}
	}

	return Closest;
}