// Copyright M9Only


#include "Character/B9CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "B9GameplayTags.h"
#include "Abandon/Abandon.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

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

FVector AB9CharacterBase::GetCombatTipLocation_Implementation(const FGameplayTag& GameplayTag)
{
	const FB9GameplayTags& GameplayTags = FB9GameplayTags::Get();
	if (GameplayTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (GameplayTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (GameplayTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (GameplayTag.MatchesTagExact(GameplayTags.CombatSocket_Others))
	{
		return GetMesh()->GetSocketLocation(OtherSocketName);
	}
	return FVector();
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

void AB9CharacterBase::Die()
{
	//这条会自动同步
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));

	MulticastHandleDeath();
}

bool AB9CharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AB9CharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AB9CharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* AB9CharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AB9CharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage: AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

int32 AB9CharacterBase::GetMinionCount_Implementation()
{
	return MinionCount;
}

void AB9CharacterBase::IncrementMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

void AB9CharacterBase::MulticastHandleDeath_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(
		this,DeadSound,GetActorLocation(),GetActorRotation());
	
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
	bDead = true;
}


void AB9CharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance,this) ;
		GetMesh()->SetMaterial(0,DynamicMatInst);
		StartDissolveTimeLine(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance,this);
		Weapon->SetMaterial(0,DynamicMatInst);
		WeaponStartDissolveTimeLine(DynamicMatInst);
	}
}
