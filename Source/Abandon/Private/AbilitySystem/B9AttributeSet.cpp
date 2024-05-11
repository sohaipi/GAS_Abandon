// Copyright M9Only


#include "AbilitySystem/B9AttributeSet.h"

#include "Net/UnrealNetwork.h"

UB9AttributeSet::UB9AttributeSet()
{
	InitHealth(250.f);
	InitMana(10.f);
	InitMaxHealth(300.f);
	InitMaxMana(200.f);
}

void UB9AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}

void UB9AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//用于通知GAS进行修改；
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Health,OldHealth);
}

void UB9AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Mana,OldMana);
}

void UB9AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,MaxHealth,OldMaxHealth);
}

void UB9AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,MaxMana,OldMaxMana);
}
