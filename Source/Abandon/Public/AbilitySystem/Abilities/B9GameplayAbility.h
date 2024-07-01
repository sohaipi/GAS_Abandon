// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "B9GameplayAbility.generated.h"

class UB9AbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ABANDON_API UB9GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category = "Input")
	FGameplayTag StartupInputTag;
};
