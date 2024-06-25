// Copyright M9Only


#include "Character/B9Character.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "Player/B9PlayerController.h"
#include "Player/B9PlayerState.h"
#include "UI/HUD/B9HUD.h"

AB9Character::AB9Character()
{
	
}

void AB9Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//init ability actor info for the server 服务器上初始化GAS对象
	InitAbilityActorInfo();
	AddCharacterAbilities();
	SetOwner(NewController);
}

void AB9Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//init info for the Client 客户端上初始化GAS的对象
	InitAbilityActorInfo();
}

int32 AB9Character::GetPlayerLevel()
{
	const AB9PlayerState* B9PlayerState = GetPlayerState<AB9PlayerState>();
	check(B9PlayerState);
	return B9PlayerState->GetPlayerLevel();
}

//初始化的具体操作, OwnerActor是PlayerState, AvatarActor是英雄的Character类
void AB9Character::InitAbilityActorInfo()
{
	AB9PlayerState* B9PlayerState = GetPlayerState<AB9PlayerState>();
	check(B9PlayerState);
	AbilitySystemComponent = B9PlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(B9PlayerState,this);

	Cast<UB9AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	AttributeSet = B9PlayerState->GetAttributeSet();

	if (AB9PlayerController* PlayerController =  Cast<AB9PlayerController>(GetController()))
	{
		if (AB9HUD* B9HUD = Cast<AB9HUD>(PlayerController->GetHUD())) 
		{
			B9HUD->InitOverlay(PlayerController,B9PlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	//只需要在服务器初始化属性，因为属性被标记为replicated;
	InitDefaultAttribute(); 
}
