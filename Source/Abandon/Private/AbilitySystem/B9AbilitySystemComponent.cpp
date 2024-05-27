// Copyright M9Only


#include "AbilitySystem/B9AbilitySystemComponent.h"

#include "B9GameplayTags.h"
#include "AbilitySystem/Abilities/B9GameplayAbility.h"

void UB9AbilitySystemComponent::AbilityActorInfoSet()
{
	//将下面的回调函数绑定在多播委托上，在instant和duration effect时调用。
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UB9AbilitySystemComponent::ClientEffectApplied);

	/*const FB9GameplayTags& GameplayTags = FB9GameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Black,
		FString::Printf(TEXT("Armor Tag: %s"),*GameplayTags.Attribute_Secondary_Armor.ToString()));*/
}

void UB9AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	
	for (const TSubclassOf<UGameplayAbility> AbilityClass :StartupAbilities)
	{ 
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		if (const UB9GameplayAbility* Ability = Cast<UB9GameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(Ability->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UB9AbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (auto AbilitySpec:GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UB9AbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (auto AbilitySpec:GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//告诉Ability输入已按下
			AbilitySpecInputPressed(AbilitySpec);
			
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UB9AbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                              const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	/*GEngine->AddOnScreenDebugMessage(1,8.f, FColor::Blue, FString("Effect Applied!"));*/
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);


}
