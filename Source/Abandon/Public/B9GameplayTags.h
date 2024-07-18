// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * B9GameplayTags，
 *
 * 用来管理游戏中Tag的单例、包含原生标签。
 */

struct FB9GameplayTags
{
public:
	static const FB9GameplayTags& Get(){return B9GameplayTags;};
	static void InitializeNativeGameplayTags();

	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;

	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;

	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;

	FGameplayTag Attribute_Resistance_Fire;
	FGameplayTag Attribute_Resistance_Lightning;
	FGameplayTag Attribute_Resistance_Arcane;
	FGameplayTag Attribute_Resistance_Physical;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_RightHand;
	FGameplayTag Montage_Attack_LeftHand;

	TMap<FGameplayTag,FGameplayTag> DamageTypesToResistance;
	
	FGameplayTag Effect_Ability_HitReact;
	
	FGameplayTag Abilities_Attack;
	
protected:

private:
	static  FB9GameplayTags B9GameplayTags;
};