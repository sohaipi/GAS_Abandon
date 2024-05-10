// Copyright M9Only


#include "UI/WidgetController/B9OverlayWidgetController.h"

#include "AbilitySystem/B9AttributeSet.h"

void UB9OverlayWidgetController::BroadcastInitValues()
{
	const UB9AttributeSet* B9AttributeSet = CastChecked<class UB9AttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(B9AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(B9AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(B9AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(B9AttributeSet->GetMaxMana());
}

void UB9OverlayWidgetController::BindCallbacksToDependencies()
{
	const UB9AttributeSet* B9AttributeSet = CastChecked<class UB9AttributeSet>(AttributeSet);

	//值变化时绑定调用回调函数
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		B9AttributeSet->GetHealthAttribute()).AddUObject(this, &UB9OverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		B9AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UB9OverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	B9AttributeSet->GetManaAttribute()).AddUObject(this, &UB9OverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		B9AttributeSet->GetMaxManaAttribute()).AddUObject(this, &UB9OverlayWidgetController::MaxManaChanged);
}

//广播数值变化
void UB9OverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const 
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UB9OverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const 
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UB9OverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UB9OverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
