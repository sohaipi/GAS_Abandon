 // Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "B9AbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API UB9AbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual  FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
