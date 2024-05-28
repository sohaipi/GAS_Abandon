// Copyright M9Only


#include "AbilitySystem/Abilities/B9ProjectileSpell.h"
#include "Interaction/CombatInterface.h"
#include "Actor/B9Projectile.h"
#include "Kismet/KismetSystemLibrary.h"


void UB9ProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	SpawnProjectile();
}

void UB9ProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetOwningActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;;
	
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatTipLocation();
		FTransform SpawnLocation;
		SpawnLocation.SetLocation(SocketLocation);
		AB9Projectile* ProjectileSpawn = GetWorld()->SpawnActorDeferred<AB9Projectile>(ProjectileClass,SpawnLocation,GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		ProjectileSpawn->FinishSpawning(SpawnLocation);
	}
}
