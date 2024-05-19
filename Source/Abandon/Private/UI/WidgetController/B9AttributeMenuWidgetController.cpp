// Copyright M9Only


#include "UI/WidgetController/B9AttributeMenuWidgetController.h"

#include "AbilitySystem/B9AttributeSet.h"




void UB9AttributeMenuWidgetController::BindCallbacksToDependencies()
{
	const UB9AttributeSet* B9AttributeSet = CastChecked<class UB9AttributeSet>(AttributeSet);
	
	/*AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				B9AttributeSet->GetHealthAttribute()).AddLambda(
					[this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);}
				);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			B9AttributeSet->GetMaxHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);}
			);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			B9AttributeSet->GetManaAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data){OnManaChanged.Broadcast(Data.NewValue);}
			);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			B9AttributeSet->GetMaxManaAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data){OnMaxManaChanged.Broadcast(Data.NewValue);}
			);*/
}

void UB9AttributeMenuWidgetController::BroadcastInitValues()
{
	const UB9AttributeSet* B9AttributeSet = CastChecked<class UB9AttributeSet>(AttributeSet);
	
	/*OnHealthChanged.Broadcast(B9AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(B9AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(B9AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(B9AttributeSet->GetMaxMana());*/
}
