// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/B9WidgetController.h"
#include "B9AttributeMenuWidgetController.generated.h"

/*DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnAttributeChangedSignature,float, NewValue);*/
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class ABANDON_API UB9AttributeMenuWidgetController : public UB9WidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitValues() override;

	/*UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;*/
};
