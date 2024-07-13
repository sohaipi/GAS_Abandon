// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "B9BTService_FindNearestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API UB9BTService_FindNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FBlackboardKeySelector TargetToFollowSelector;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;
	
};
