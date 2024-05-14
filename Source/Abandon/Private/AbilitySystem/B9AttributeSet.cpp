// Copyright M9Only


#include "AbilitySystem/B9AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"



UB9AttributeSet::UB9AttributeSet()
{
	InitHealth(10.f);
	InitMana(50.f);
	InitMaxHealth(200.f);
	InitMaxMana(500.f);
}

void UB9AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UB9AttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}

//Pre之后，数值仍可能被更改，不能以最终值看待。
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
void UB9AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectSourceProperties Props)
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

