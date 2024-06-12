// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "B9AttributeSet.generated.h"
//Ctl H替换
//源码定义好的宏，用于使用四个对属性操作的函数。
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//用个委托，把属性的Tag与AS中返回属性的GETTER绑定起来，实现tag与属性的对应。
//参数在前，签名在后;
//用函数指针版本替代了。
/*DECLARE_DELEGATE_RetVal(FGameplayAttribute,FAttributeSignature);*/


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


/*typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;*/
//将函数指针定义为模板使用；
template<class T>
using TStaticFunPtr =typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr ;


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
	
	//繁琐的delegate版本，用函数指针替代
	/*TMap<FGameplayTag,FAttributeSignature> TagsToAttributes;*/
	TMap<FGameplayTag,TStaticFunPtr<FGameplayAttribute()>> TagsToAttributes;

	//用于表示一个返回FGameplayAttribute类型函数的指针，如 FunctionPtr = GetStrengthAttribute(); 
	/*TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FunctionPtr ;*/
	
	//构造新属性的样板步骤boilerplate；
	//Step1 声明。同时发起OnRep函数。底下的宏用于引入属性库？
	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Strength);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Intelligence);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Resilience);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Vigor);

	/*
	* Vital Attributes
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Mana);

	/*
	* Secondary Attributes
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,MaxHealth);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,MaxMana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor; //Reduces damage taken, improves Block Chance
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,Armor);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration; //Ignores percentage of enemy Armor, increases Crit Hit Chance
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,ArmorPenetration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;//Chance to cut incoming damage in half
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,BlockChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;//Chance to double damage plus critical hit bonus
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,CriticalHitChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;//Bonus damage added when a critical hit is scored
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,CriticalHitDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;//Reduces critical hit chance of attacking enemies
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,CriticalHitResistance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;//Amount of Health regenerated every 1 second
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,HealthRegeneration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;//Amount of Mana regenerated every 1 second
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,ManaRegeneration);


	/*
	* Meta Attributes
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UB9AttributeSet,IncomingDamage);

	
	//使用 （const a& b） 的引用声明，使频繁被调用时，降低开销。 使用 a() const,保证不能修改所属类的非静态成员变量。
	//Step2 通知函数
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	
private:
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectSourceProperties& Props)const;
	//多了下面这句导致崩溃吗?
	/*UPROPERTY()
	FEffectSourceProperties EffectSourceProperties;*/
};
