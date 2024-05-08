// Copyright M9Only


#include "Character/B9Character.h"

#include "AbilitySystemComponent.h"
#include "Player/B9PlayerState.h"

AB9Character::AB9Character()
{
	
}

void AB9Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//init ability actor info for the server 服务器上初始化GAS对象
	InitAbilityActorInfo();
}

void AB9Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//init info for the Client 客户端上初始化GAS的对象
	InitAbilityActorInfo();
}

//初始化的具体操作
void AB9Character::InitAbilityActorInfo()
{
	AB9PlayerState* B9PlayerState = GetPlayerState<AB9PlayerState>();
	check(B9PlayerState);
	B9PlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(B9PlayerState,this);
	AbilitySystemComponent = B9PlayerState->GetAbilitySystemComponent();
	AttributeSet = B9PlayerState->GetAttributeSet();
}
