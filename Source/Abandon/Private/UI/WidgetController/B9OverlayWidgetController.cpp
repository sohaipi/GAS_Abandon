// Copyright M9Only


#include "UI/WidgetController/B9OverlayWidgetController.h"

#include "AbilitySystem/B9AbilitySystemComponent.h"
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

	//使用Lambda简化委托的调用结构（注释块一、二）
	//Lambda表达式可以捕获并访问其定义上下文中的变量，从而提供了一种方便的方式来编写内联函数和回调函数。
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
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
			);
	
	/* 注释块一
	 //值变化时绑定调用回调函数 ，调用broadcast以实现触发委托函数。
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		B9AttributeSet->GetHealthAttribute()).AddUObject(this, &UB9OverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		B9AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UB9OverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	B9AttributeSet->GetManaAttribute()).AddUObject(this, &UB9OverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		B9AttributeSet->GetMaxManaAttribute()).AddUObject(this, &UB9OverlayWidgetController::MaxManaChanged);*/
	

	//lambda的使用。由多播激活函数体。[capture list] (parameter list) -> return type { function body }
	Cast<UB9AbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (FGameplayTag Tag:AssetTags)
			{
				FGameplayTag MsgTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MsgTag))
				{
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);

					MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
				/*const FString Msg = FString::Printf(TEXT("GE Tag: %s"),*Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1,8.f, FColor::Blue, FString(Msg));*/
				
			}
		}
		);
}

//注释块二
//broadcast用于触发多播委托的调用
/*void UB9OverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const 
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
}*/
