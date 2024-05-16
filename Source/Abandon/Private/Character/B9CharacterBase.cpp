// Copyright M9Only


#include "Character/B9CharacterBase.h"

#include "AbilitySystemComponent.h"

AB9CharacterBase::AB9CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponStr");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AB9CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AB9CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AB9CharacterBase::InitAbilityActorInfo()
{
}

void AB9CharacterBase::InitPrimaryAttribute()
{
	
	const FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
	 	DefaultPrimaryAttributes,1.f,EffectContextHandle);
	/*GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget()*/
}

