// Copyright M9Only


#include "AbilitySystem/B9AbilitySystemComponent.h"

void UB9AbilitySystemComponent::AbilityActorInfoSet()
{
	//将下面的回调函数绑定在多播委托上，在instant和duration effect时调用。
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UB9AbilitySystemComponent::EffectApplied);
}

void UB9AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	/*GEngine->AddOnScreenDebugMessage(1,8.f, FColor::Blue, FString("Effect Applied!"));*/
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);


}
