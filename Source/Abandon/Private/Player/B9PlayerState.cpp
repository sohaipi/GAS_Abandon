// Copyright M9Onl y


#include "Player/B9PlayerState.h"

#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "AbilitySystem/B9AttributeSet.h"
#include "Net/UnrealNetwork.h"

AB9PlayerState::AB9PlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UB9AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//Gameplay Effects are replicated to the owning client only. Gameplay Cues and Gameplay Tags replicated to all clients.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UB9AttributeSet>("AttributeSet");
	//为了ASC提高同步率；
	NetUpdateFrequency = 100.f;
}

void AB9PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AB9PlayerState,Level);
}

UAbilitySystemComponent* AB9PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AB9PlayerState::OnRep_Level(int OldLevel)
{
}
