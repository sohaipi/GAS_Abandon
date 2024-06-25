// Copyright M9Only


#include "AbilitySystem/B9AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "B9GameplayTags.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/B9PlayerController.h"


UB9AttributeSet::UB9AttributeSet()
{
	const FB9GameplayTags& GameplayTags = FB9GameplayTags::Get();

	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Strength ,GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Intelligence ,GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Resilience ,GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Vigor ,GetVigorAttribute);
	
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Armor ,GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ArmorPenetration ,GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_BlockChance ,GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitChance ,GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitDamage ,GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitResistance ,GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_HealthRegeneration ,GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ManaRegeneration ,GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxHealth ,GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxMana ,GetMaxManaAttribute);
	//Delegate版本
	/*FAttributeSiganature StrengthDelegate;
	StrengthDelegate.BindStatic(GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Strength,StrengthDelegate);*/
	
}

void UB9AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Strength,COND_None,REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Mana,COND_None,REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
}

//Pre之后，数值仍可能被更改，不能以最终值看待。对修饰符将导致的结果进行限制。
void UB9AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxHealth());
		/*UE_LOG(LogTemp,Warning,TEXT("Health: %f"),NewValue);*/
		
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxMana());
		/*UE_LOG(LogTemp,Warning,TEXT("Mana: %f"),NewValue);*/
	}
}
void UB9AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectSourceProperties& Props) const
{
	Props.EffectContextHandle =  Data.EffectSpec.GetContext();
	
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}




void UB9AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectSourceProperties Props;
	SetEffectProperties(Data,Props);

	//最终限制住属性数值。
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
		/*UE_LOG(LogTemp,Warning,TEXT("%s,发生血量变化：%f"),*Props.TargetAvatarActor->GetName(),GetHealth());*/
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0.f,GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float	LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth,0.f,GetMaxHealth()));

			const bool bFatal = NewHealth <=0.f;
			if (bFatal)
			{
				if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor))
				{
					CombatInterface->Die();
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FB9GameplayTags::Get().Effect_Ability_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
			ShowFloatingText(Props,LocalIncomingDamage);
		}
	}
}
void UB9AttributeSet::ShowFloatingText(const FEffectSourceProperties& Props, float Damage) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AB9PlayerController* PC = Cast<AB9PlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter,0)) )
		{
			PC->ShowDamageNumber(Damage,Props.TargetCharacter);
		}
	}
}

void UB9AttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Strength,OldStrength);
}

void UB9AttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Intelligence,OldIntelligence);
}

void UB9AttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Resilience,OldResilience);
}

void UB9AttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Vigor,OldVigor);
}

void UB9AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//用于通知GAS进行修改；
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Health,OldHealth);
}

void UB9AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Mana,OldMana);
}

void UB9AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,MaxHealth,OldMaxHealth);
}

void UB9AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,MaxMana,OldMaxMana);
}

void UB9AttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,Armor,OldArmor);
}

void UB9AttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,ArmorPenetration,OldArmorPenetration);
}

void UB9AttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,BlockChance,OldBlockChance);
}

void UB9AttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,CriticalHitChance,OldCriticalHitChance);
}

void UB9AttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,CriticalHitDamage,OldCriticalHitDamage);
}

void UB9AttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,CriticalHitResistance,OldCriticalHitResistance);
}

void UB9AttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,HealthRegeneration,OldHealthRegeneration);
}

void UB9AttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UB9AttributeSet,ManaRegeneration,OldManaRegeneration);
}

