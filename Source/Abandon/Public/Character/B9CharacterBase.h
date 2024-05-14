// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "B9CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
//添加abstract使该类不可被拖入关卡；
class ABANDON_API AB9CharacterBase : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AB9CharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat" )
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//提升到base使多播委托的绑定在此函数中执行。
	virtual void InitAbilityActorInfo();
};
