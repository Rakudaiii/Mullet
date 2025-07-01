#include "Actors/MDJDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/Character/MDJMainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Curves/CurveFloat.h"

AMDJDoor::AMDJDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorStaticMesh"));
	LeftDoor->SetupAttachment(RootComponent);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoorStaticMesh"));
	RightDoor->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AMDJDoor::BeginPlay()
{
	Super::BeginPlay();

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMDJDoor::HandleOverlap);
	}

	LeftInitialLocation = LeftDoor->GetRelativeLocation();
	RightInitialLocation = RightDoor->GetRelativeLocation();

	if (DoorCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleDoorProgress"));

		DoorTimeline.AddInterpFloat(DoorCurve, ProgressFunction);
		DoorTimeline.SetLooping(false);
		DoorTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	}
}
void AMDJDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DoorTimeline.TickTimeline(DeltaTime);
}

void AMDJDoor::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	if (Cast<AMDJMainCharacter>(OtherActor))
	{
		OpenDoor();
	}
}

void AMDJDoor::OpenDoor()
{
	if (DoorTimeline.IsPlaying())
		return;

	DoorTimeline.PlayFromStart();
}

void AMDJDoor::HandleDoorProgress(float Value)
{
	const float LeftXOffset = FMath::Lerp(0.0f, DoorMoveDistance, Value);
	const float RightXOffset = FMath::Lerp(0.0f, -DoorMoveDistance, Value);

	FVector NewLeftLocation = LeftInitialLocation;
	NewLeftLocation.X += LeftXOffset;

	FVector NewRightLocation = RightInitialLocation;
	NewRightLocation.X += RightXOffset;

	LeftDoor->SetRelativeLocation(NewLeftLocation);
	RightDoor->SetRelativeLocation(NewRightLocation);
}
