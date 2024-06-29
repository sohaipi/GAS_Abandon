// Copyright M9Only


#include "AbilitySystem/B9AbilitySystemGlobals.h"

#include "B9AbilitySystemTypes.h"

FGameplayEffectContext* UB9AbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FB9GameplayEffectContext();
}
