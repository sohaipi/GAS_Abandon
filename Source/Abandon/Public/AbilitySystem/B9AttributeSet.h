// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "B9AttributeSet.generated.h"

//源码定义好的宏，用于使用四个对属性操作的函数。
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//Ctl H替换

USTRUCT()
struct FEffectSourceProperties
{
	GENERATED_BODY()

	FEffectSourceProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

	
	/*
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AActor> TargetAvatarActor = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AController> TargetController = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<ACharacter> TargetCharacter = nullptr;*/
};
/**
 * 
 */
UCLASS()
class ABANDON_API UB9AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UB9AttributeSet();
	//Step3 通知具体复制内容的函数~
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/*virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;*/
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	
	//构造新属性的样板步骤boilerplate；
	//Step1 声明。同时发起OnRep函数。底下的宏用于引入属性库？
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,MaxMana);

	UPROPERTY()
	FEffectSourceProperties EffectSourceProperties;
	//使用 （const a& b） 的引用声明，使频繁被调用时，降低开销。 使用 a() const,保证不能修改所属类的非静态成员变量。
	//Step2 通知函数
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectSourceProperties Props);
};
