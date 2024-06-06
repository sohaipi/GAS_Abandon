// Copyright M9Only


#include "AbilitySystem/Abilities/B9ProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "B9GameplayTags.h"
#include "Interaction/CombatInterface.h"
#include "Actor/B9Projectile.h"


void UB9ProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UB9ProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetOwningActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;;
	
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatTipLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		AB9Projectile* ProjectileSpawn = GetWorld()->SpawnActorDeferred<AB9Projectile>(ProjectileClass,SpawnTransform,GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle DamageSpecHandle = SourceAsc->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),SourceAsc->MakeEffectContext());

		FB9GameplayTags GameplayTags = FB9GameplayTags::Get();
		//TODO 将数值用技能等级拆分
		//根据tag查找 magnitude;
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle,GameplayTags.Damage,50.f);
		ProjectileSpawn->DamageEffectSpecHandle = DamageSpecHandle;
		
		ProjectileSpawn->FinishSpawning(SpawnTransform);
	}
}
