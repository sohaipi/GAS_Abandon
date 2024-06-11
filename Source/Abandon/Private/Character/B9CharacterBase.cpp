// Copyright M9Only


#include "Character/B9CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Abandon/Abandon.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"

AB9CharacterBase::AB9CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponStr");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AB9CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AB9CharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AB9CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AB9CharacterBase::GetCombatTipLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AB9CharacterBase::InitAbilityActorInfo()
{
}

void AB9CharacterBase::InitDefaultAttribute() const
{
	ApplyEffectToTarget(DefaultPrimaryAttributes,1.0);
	ApplyEffectToTarget(DefaultSecondaryAttributes,1.0);
	ApplyEffectToTarget(DefaultVitalAttributes,1.0);
}

void AB9CharacterBase::ApplyEffectToTarget(TSubclassOf<UGameplayEffect> DefaultAttributes, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultAttributes);
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		 DefaultAttributes,Level,EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
}

void AB9CharacterBase::AddCharacterAbilities()
{
	UB9AbilitySystemComponent* B9ASC = CastChecked<UB9AbilitySystemComponent>(AbilitySystemComponent);
	//只允许在服务器添加
	if (!HasAuthority()) return;
	B9ASC->AddCharacterAbilities(StartupAbilities);
}

