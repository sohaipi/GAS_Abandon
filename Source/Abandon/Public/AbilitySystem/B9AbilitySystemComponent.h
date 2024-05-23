// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "B9AbilitySystemComponent.generated.h"
//用于广播到overlay widget controller
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer& /*Asset Tags*/)
/**
 * 
*/	
UCLASS()
class ABANDON_API UB9AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	//响应输入用
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	
protected:
	//用于绑定多播委托。
	void EffectApplied(
		UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& GameplayEffectSpec,
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
};
