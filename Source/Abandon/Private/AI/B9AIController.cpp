// Copyright M9Only


#include "AI/B9AIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AB9AIController::AB9AIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComp");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");
	check(BehaviorTreeComponent);
}
