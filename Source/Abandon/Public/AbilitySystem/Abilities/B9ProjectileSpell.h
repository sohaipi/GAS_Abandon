// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/B9GameplayAbility.h"
#include "B9ProjectileSpell.generated.h"

class AB9Projectile;
/**
 * 
 */
UCLASS()
class ABANDON_API UB9ProjectileSpell : public UB9GameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AB9Projectile> ProjectileClass;

	UFUNCTION(BlueprintCallable,Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
};
