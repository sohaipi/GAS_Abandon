// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "B9PlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * GASNote:OwnerActor需要继承并实现IAbilitySystemInterface,
 * 如果AvatarActor和OwnerActor是不同的Actor,
 * 那么AvatarActor也应该继承并实现IAbilitySystemInterface.
 * 该接口有一个必须重写的函数, UAbilitySystemComponent* GetAbilitySystemComponent() const,
 * 其返回一个指向ASC的指针, ASC通过寻找该接口函数来和系统内部进行交互.
 */
UCLASS()
class ABANDON_API AB9PlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
	AB9PlayerState();
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
