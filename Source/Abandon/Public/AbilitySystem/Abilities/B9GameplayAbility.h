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

	//默认所有此类都有伤害，无伤害的使用父类；
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Damage")
	FScalableFloat Damage;
};
