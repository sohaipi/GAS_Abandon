// Copyright M9Only


#include "UI/WidgetController/B9AttributeMenuWidgetController.h"

#include "B9GameplayTags.h"
#include "AbilitySystem/B9AttributeSet.h"




void UB9AttributeMenuWidgetController::BindCallbacksToDependencies()
{

}

void UB9AttributeMenuWidgetController::BroadcastInitValues()
{
	const UB9AttributeSet* B9AttributeSet = CastChecked<class UB9AttributeSet>(AttributeSet);
	
	check(B9AttributeInfo);
	FB9AttributeInformation Info = B9AttributeInfo->FindAttributeInfoForTag(FB9GameplayTags::Get().Attribute_Primary_Strength);
	Info.AttributeValue = B9AttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
