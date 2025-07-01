
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "MDJAIController.generated.h"



UCLASS()
class MULLETMADJACK_API AMDJAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	
};
