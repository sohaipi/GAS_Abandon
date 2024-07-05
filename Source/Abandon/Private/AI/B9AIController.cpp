// Copyright M9Only


#include "AI/B9AIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

AB9AIController::AB9AIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");
	check(BehaviorTreeComponent);
}
