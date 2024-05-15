// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/B9WidgetController.h"
#include "B9OverlayWidgetController.generated.h"


//用于读取Tag在界面显示widget
USTRUCT(BlueprintType)
struct FUIWidgetRow: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	//加括号调用默认构造函数 FGameplayTag()
	FGameplayTag MessageTage = FGameplayTag();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class UB9UserWidget> MessageWidget;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

class UB9UserWidget;

//简化下面的声明，GAS中属性变化通过获取不同属性值进行传递；
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnAttributeChangedSignature,float, NewValue);
//多播委托，和签名；通过访问UB9OverlayWidgetController实例的多播委托并使用AddDynamic方法将自定义函数绑定到这些委托。
//当相应的属性值发生变化时，这些自定义函数将被自动调用。
/*DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnHealthChangedSignature,float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnMaxHealthChangedSignature,float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnManaChangedSignature,float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FOnMaxManaChangedSignature,float, NewMaxMana);*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FMessageWidgetRowSignature,FUIWidgetRow, Row);


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
	
	//将这些多播委托作为UPROPERTY成员变量添加到UB9OverlayWidgetController类中。这样，其他类可以在运行时访问和绑定这些委托。
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable,Category = "GAS|Message")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = " Wdiget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	//回调函数,用于在多播中调用；
	/*void HealthChanged(const FOnAttributeChangeData& Data) const ;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const ;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;*/

	template <typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
};

template <typename T>
T* UB9OverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return  DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}

