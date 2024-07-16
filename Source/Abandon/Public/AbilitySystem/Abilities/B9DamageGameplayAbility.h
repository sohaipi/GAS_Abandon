// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/B9GameplayAbility.h"
#include "B9DamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API UB9DamageGameplayAbility : public UB9GameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly,Category = "Damage")
	TMap<FGameplayTag,FScalableFloat> DamageTypes;
};
