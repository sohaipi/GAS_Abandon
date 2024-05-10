// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/B9WidgetController.h"
#include "B9OverlayWidgetController.generated.h"
//多播委托，和签名
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnHealthChangedSignature,float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnMaxHealthChangedSignature,float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnManaChangedSignature,float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnMaxManaChangedSignature,float, NewMaxMana);
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class ABANDON_API UB9OverlayWidgetController : public UB9WidgetController
{
	GENERATED_BODY()

public: 
	virtual void BroadcastInitValues() override;
	virtual void BindCallbacksToDependencies() override;

	//绑定上面的多播委托，用来广播和触发函数
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:
	//回调函数
	void HealthChanged(const FOnAttributeChangeData& Data) const ;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const ;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};

