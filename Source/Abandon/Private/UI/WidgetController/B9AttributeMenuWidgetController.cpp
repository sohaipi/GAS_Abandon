// Copyright M9Only


#include "UI/WidgetController/B9AttributeMenuWidgetController.h"


#include "AbilitySystem/B9AttributeSet.h"




void UB9AttributeMenuWidgetController::BindCallbacksToDependencies()
{
	const UB9AttributeSet* B9AttributeSet = CastChecked<class UB9AttributeSet>(AttributeSet);
	for (auto& Pair:B9AttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[Pair,this](const FOnAttributeChangeData& Data)
		{	
			BroadcastAttributeInfo(Pair.Key,Pair.Value());
		}
		);
	}

}

void UB9AttributeMenuWidgetController::BroadcastInitValues()
{
	const UB9AttributeSet* B9AttributeSet = CastChecked<class UB9AttributeSet>(AttributeSet);
	
	check(B9AttributeInfo);

	for (auto& Pair:B9AttributeSet->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
		/*FB9AttributeInformation Info = B9AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(B9AttributeSet);*/
		
		/*Info.AttributeValue = Pair.Value.Execute().GetNumericValue(B9AttributeSet);*/
		
		/*AttributeInfoDelegate.Broadcast(Info);*/
	}
	
	/*
	 *没做tag与属性的map对应时的暴力广播,用函数指针替代
	FB9AttributeInformation Info = B9AttributeInfo->FindAttributeInfoForTag(FB9GameplayTags::Get().Attribute_Primary_Strength);
	Info.AttributeValue = B9AttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);

	FB9AttributeInformation IntellInfo = B9AttributeInfo->FindAttributeInfoForTag(FB9GameplayTags::Get().Attribute_Primary_Intelligence);
	IntellInfo.AttributeValue = B9AttributeSet->GetIntelligence();
	AttributeInfoDelegate.Broadcast(IntellInfo);*/
	
}

void UB9AttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute)const
{
	FB9AttributeInformation Info = B9AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
