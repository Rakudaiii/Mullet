#include "AI/MDJAIController.h"

void AMDJAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTreeAsset)
		RunBehaviorTree(BehaviorTreeAsset);
	
	
	
}
