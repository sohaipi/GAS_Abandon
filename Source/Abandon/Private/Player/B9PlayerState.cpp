// Copyright M9Only


#include "Player/B9PlayerState.h"

#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "AbilitySystem/B9AttributeSet.h"
#include "Net/UnrealNetwork.h"

AB9PlayerState::AB9PlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UB9AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UB9AttributeSet>("AttributeSet");
	
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
