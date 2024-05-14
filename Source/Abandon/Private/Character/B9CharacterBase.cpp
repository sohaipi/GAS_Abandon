// Copyright M9Only


#include "Character/B9CharacterBase.h"

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

