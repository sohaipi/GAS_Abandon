// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/B9WidgetController.h"
#include "AbilitySystem/Data/B9AttributeInfo.h"
#include "B9AttributeMenuWidgetController.generated.h"

struct FB9AttributeInformation;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FAttributeInfoSignature,const FB9AttributeInformation&,Info);

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

	UPROPERTY(BlueprintAssignable,Category = "GAS")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UB9AttributeInfo> B9AttributeInfo;

private:
	
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute)const;
};
