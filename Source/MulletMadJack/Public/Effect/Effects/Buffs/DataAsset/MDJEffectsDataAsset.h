#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "MDJEffectsDataAsset.generated.h"

//Shock Pulse
USTRUCT(BlueprintType)
struct FShockPulseParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Shock Pulse"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Chance = 100;
};

USTRUCT(BlueprintType)
struct FShockPulseDebug
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebug = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Segments = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Blue;
};

//Slow Field
USTRUCT(BlueprintType)
struct FSlowFieldParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Slow Field"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedDecrease = 200.0f;
};

USTRUCT(BlueprintType)
struct FSlowFieldDebug
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebug = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Segments = 64.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZOffset = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Green;
};

//Jump EMP
USTRUCT(BlueprintType)
struct FJumpEmpParameters
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Jump EMP"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResetTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Chance = 100;
};

USTRUCT(BlueprintType)
struct FJumpEmpDebug
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebug = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Segments = 64.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZOffset = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Purple;
};


USTRUCT(BlueprintType)
struct FReflectShotParameters
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Reflect Shot"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Chance = 100;
};

USTRUCT(BlueprintType)
struct FKillShieldParameters
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Kill Shield"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResetTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Chance = 100;
};

USTRUCT(BlueprintType)
struct FDeflectShield
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Deflect Shield"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinChance = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxChance = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationTime = 1.5f;
};

USTRUCT(BlueprintType)
struct FGhostSlideParameters
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Ghost Slide"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Chance = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 5000.0f;
};

USTRUCT(BlueprintType)
struct FGhostSlideDebug
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebug = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Segments = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Blue;
};

USTRUCT(BlueprintType)
struct FBerserkModeParameters
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Berserk Mode"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TriggerHealth = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeedMultiplier = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlideSpeedMultiplier = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashSpeedMultiplier = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GunDamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedDecrease = 200.0f;

	
};

UCLASS()
class MULLETMADJACK_API UMDJEffectsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllDebug")
	bool RemoveAllDebug = false;

	//Shock Pulse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShockPulse")
	FShockPulseParameters ShockPulseParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShockPulse")
	FShockPulseDebug ShockPulseDebug;

	//Slow Field
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlowField")
	FSlowFieldParameters SlowFieldParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlowField")
	FSlowFieldDebug SlowFieldDebug;

	//Jump EMP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpEMP")
	FJumpEmpParameters JumpEmpParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpEMP")
	FJumpEmpDebug JumpEmpDebug;

	//ReflectShot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReflectShot")
	FReflectShotParameters ReflectShotParameters;

	//Kill Shield
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillShield")
	FKillShieldParameters KillShieldParameters;

	//Deflect Shield
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeflectShield")
	FDeflectShield DeflectShield;

	//GhostSlide
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GhostSlide")
	FGhostSlideParameters GhostSlideParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GhostSlide")
	FGhostSlideDebug GhostSlideDebug;

	//BerserMode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berserk Mode")
	FBerserkModeParameters BerserkModeParameters;
};
