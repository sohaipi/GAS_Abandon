// Copyright M9Only


#include "AbilitySystem/B9AbilitySystemComponent.h"

#include "B9GameplayTags.h"

void UB9AbilitySystemComponent::AbilityActorInfoSet()
{
	//将下面的回调函数绑定在多播委托上，在instant和duration effect时调用。
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UB9AbilitySystemComponent::EffectApplied);

	/*const FB9GameplayTags& GameplayTags = FB9GameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Black,
		FString::Printf(TEXT("Armor Tag: %s"),*GameplayTags.Attribute_Secondary_Armor.ToString()));*/
}

void UB9AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	/*GEngine->AddOnScreenDebugMessage(1,8.f, FColor::Blue, FString("Effect Applied!"));*/
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);


}
