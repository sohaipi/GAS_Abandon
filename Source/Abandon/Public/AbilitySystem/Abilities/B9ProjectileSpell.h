// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "B9DamageGameplayAbility.h"
#include "B9ProjectileSpell.generated.h"

class AB9Projectile;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class ABANDON_API UB9ProjectileSpell : public UB9DamageGameplayAbility
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
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool  bOverridePitch = false;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float  ProjectilePitchOverride = 0.f;
	
	UFUNCTION(BlueprintCallable,Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag);
	
};
