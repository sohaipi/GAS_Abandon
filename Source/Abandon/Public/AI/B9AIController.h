// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "B9AIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
/**
 * 
 */
UCLASS()
class ABANDON_API AB9AIController : public AAIController
{
	GENERATED_BODY()
public:
	AB9AIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
	