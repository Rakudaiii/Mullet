#include "MulletMadJack/Public/Components/MDJHealthComponent.h"


//Log
DEFINE_LOG_CATEGORY(HealthComponent);

UMDJHealthComponent::UMDJHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMDJHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	StartAutoHPDecrease();
}


//Category - Component
void UMDJHealthComponent::Initialize(const float InHealth)
{
	CurrenHealth = InHealth;
	MaxHealth = CurrenHealth;
}


//Category - Health

void UMDJHealthComponent::TakeDamage(const float InDamage, AActor* DamagedActor)
{
	if (!bDead)
	{
		UE_LOG(HealthComponent, Log, TEXT("Player isn't dead"));

		UE_LOG(HealthComponent, Log, TEXT("Damage: %s"), *FString::SanitizeFloat(InDamage));
		if (DamagedActor)
		{
			OnTakeDamage.Broadcast(DamagedActor);
		}

		if (!bGodMode)
		{
			CurrenHealth = FMath::Clamp(CurrenHealth - InDamage, 0.0f, MaxHealth);
			OnHealthChanged.Broadcast(CurrenHealth);
			IsDead(CurrenHealth);
		}
	}
	else
	{
		UE_LOG(HealthComponent, Log, TEXT("Player is dead"));
	}
}


bool UMDJHealthComponent::IsDead(const float InHealth)
{
	if (InHealth <= 0.0f)
	{
		bDead = true;
		OnDead.Broadcast();
		UE_LOG(HealthComponent, Log, TEXT("Name's dead:%s"), *GetOwner()->GetName());
	}

	return bDead;
}

void UMDJHealthComponent::EnableGodMode(FName BuffName, float Duration, float Chance)
{
	if (FMath::RandRange(0, 99) >= Chance)
		return;

	if (GodModeTimers.Contains(BuffName))
	{
		GetWorld()->GetTimerManager().ClearTimer(GodModeTimers[BuffName]);
	}

	ActiveGodModeSources.Add(BuffName);
	bGodMode = true;

	FTimerHandle& TimerHandle = GodModeTimers.FindOrAdd(BuffName);

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this, BuffName]()
		{
			ActiveGodModeSources.Remove(BuffName);
			GodModeTimers.Remove(BuffName);
			bGodMode = (ActiveGodModeSources.Num() > 0);
		},
		Duration,
		false
	);
}

void UMDJHealthComponent::GainHealth(const float InValue)
{
	CurrenHealth = FMath::Clamp(CurrenHealth + InValue, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrenHealth);
}


//Category - AutoHealthDecrease

void UMDJHealthComponent::StartAutoHPDecrease()
{
	if (bAutoTickHP)
	{
		GetWorld()->GetTimerManager().SetTimer(HPDecreaseTimerHandle, this, &UMDJHealthComponent::HPDecrease, TickTime,
		                                       true);
	}
}

void UMDJHealthComponent::StopAutoHPDecrease()
{
	if (HPDecreaseTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(HPDecreaseTimerHandle);
	}
}

void UMDJHealthComponent::HPDecrease()
{
	//TakeDamage(TickDamage);
	CurrenHealth = FMath::Clamp(CurrenHealth - TickDamage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrenHealth);
	IsDead(CurrenHealth);
}
