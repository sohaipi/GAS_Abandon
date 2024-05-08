// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "B9WidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;


/**
 *整合控制器的四个关键参数。
 *在C++中，构造函数的声明和定义通常不需要在末尾加上分号（;）。
 *这是因为构造函数的定义本身就是一个完整的语句，包括函数签名、初始化列表（可选）和函数体。
 *两个构造函数都在结构体定义内部实现，所以它们的末尾不需要分号。
 *如果在结构体定义外部实现构造函数，那么需要在结构体定义末尾加上分号来表示定义的结束。
 **
 *: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS)：这部分代码是构造函数的初始化列表。
 *初始化列表在构造函数体之前执行，并用于初始化成员变量。
 *初始化列表将传递给构造函数的参数值分别赋给PlayerController、PlayerState、AbilitySystemComponent和AttributeSet成员变量。
 **/
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS)	{}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class ABANDON_API UB9WidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams( const FWidgetControllerParams& WCParams);

	//放结构体中
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
