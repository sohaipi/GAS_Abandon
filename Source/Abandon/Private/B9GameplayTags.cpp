// Copyright M9Only


#include "B9GameplayTags.h"

#include "GameplayTagsManager.h"

FB9GameplayTags FB9GameplayTags::B9GameplayTags;

void FB9GameplayTags::InitializeNativeGameplayTags()
{
	//Vital Attributes
	B9GameplayTags.Attribute_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Health"),FString("Health"));
	B9GameplayTags.Attribute_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Mana"),FString("Mana"));

	//Primary Attributes
	B9GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),FString("Increases physical damage"));
	B9GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),FString("Increases magic damage"));
	B9GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),FString("Increases Armor and ArmorPenetration"));
	B9GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),FString("Increases health"));

	//Secondary Attributes
	B9GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),FString("Reduces damage taken, improves Block Chance"));
	B9GameplayTags.Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),FString("Ignores percentage of enemy Armor, increases Crit Hit Chance"));
	B9GameplayTags.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),FString("Chance to cut incoming damage in half"));
	B9GameplayTags.Attribute_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),FString("Chance to double damage plus critical hit bonus"));
	B9GameplayTags.Attribute_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),FString("Bonus damage added when a critical hit is scored"));
	B9GameplayTags.Attribute_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),FString("Reduces critical hit chance of attacking enemies"));
	B9GameplayTags.Attribute_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),FString("Amount of Health regenerated every 1 second"));
	B9GameplayTags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),FString("Amount of Mana regenerated every 1 second"));
	B9GameplayTags.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),FString("MaxHealth"));
	B9GameplayTags.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),FString("MaxMana"));

	//Resistance Attributes
	B9GameplayTags.Attribute_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),FString("Reduces Fire damage taken"));
	B9GameplayTags.Attribute_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),FString("Reduces Lightning damage taken"));
	B9GameplayTags.Attribute_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),FString("Reduces Arcane damage taken"));
	B9GameplayTags.Attribute_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),FString("Reduces Physical damage taken"));

	//Input Tags
	B9GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),FString("InputTag:LMB"));
	B9GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),FString("InputTag:RMB"));
	B9GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),FString("InputTag:Keyboard_1"));
	B9GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),FString("InputTag:Keyboard_2"));
	B9GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),FString("InputTag:Keyboard_3"));
	B9GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),FString("InputTag:Keyboard_4"));
	
	//Abilities Tags
	B9GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage"),FString("Damage"));
	
	/*
	 *伤害类型
	 */
	B9GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Fire"),FString("Fire Damage Type"));
	B9GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Lightning"),FString("Lightning Damage Type"));
	B9GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Arcane"),FString("Arcane Damage Type"));
	B9GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Physical"),FString("Physical Damage Type"));

	/* 
	 * 攻击用武器类型标签;
	 */
	B9GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Weapon"),FString("CombatSocket.Weapon"));
	B9GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.LeftHand"),FString("CombatSocket.LeftHand"));
	B9GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.RightHand"),FString("CombatSocket.RightHand"));
	B9GameplayTags.CombatSocket_Others = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Others"),FString("CombatSocket.Others"));

	/*
	 * 蒙太奇区分标签
	 */
	B9GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.1"),FString("Montage.Attack.1"));
	B9GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.2"),FString("Montage.Attack.2"));
	B9GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.3"),FString("Montage.Attack.3"));
	B9GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.4"),FString("Montage.Attack.4"));
	
	
	/*
	 *元素抗性与元素伤害的对照关系；
	 */
	B9GameplayTags.DamageTypesToResistance.Add(B9GameplayTags.Damage_Fire,B9GameplayTags.Attribute_Resistance_Fire);
	B9GameplayTags.DamageTypesToResistance.Add(B9GameplayTags.Damage_Lightning,B9GameplayTags.Attribute_Resistance_Lightning);
	B9GameplayTags.DamageTypesToResistance.Add(B9GameplayTags.Damage_Arcane,B9GameplayTags.Attribute_Resistance_Arcane);
	B9GameplayTags.DamageTypesToResistance.Add(B9GameplayTags.Damage_Physical,B9GameplayTags.Attribute_Resistance_Physical);
	
	B9GameplayTags.Effect_Ability_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Effect.Ability.HitReact"),FString("Damage React"));

	/*
	 *技能类型标签,用于在Ability中识别
	 */
	B9GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Attack"),FString("AbilityAttack Tag"));
	B9GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Summon"),FString("AbilitySummon Tag"));
}
