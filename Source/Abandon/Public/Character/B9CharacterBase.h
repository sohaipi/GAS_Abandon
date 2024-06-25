// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "B9CharacterBase.generated.h"

class UAnimMontage;
class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
//添加abstract使该类不可被拖入关卡；
class ABANDON_API AB9CharacterBase : public ACharacter , public IAbilitySystemInterface , public  ICombatInterface
{
	GENERATED_BODY()

public:
	AB9CharacterBase();
	//来自于IAbilitySystemInterface的虚函数；
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat" )
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;
	virtual FVector GetCombatTipLocation() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	//提升到base使多播委托的绑定在此函数中执行。
	virtual void InitAbilityActorInfo();

	virtual void InitDefaultAttribute() const;
	void ApplyEffectToTarget(TSubclassOf<UGameplayEffect> DefaultAttributes, float Level) const;

	void AddCharacterAbilities();

	//只在服务器处理一些内容；
	virtual void Die() override;
 
	//死亡具体行为需要同步;
	UFUNCTION(NetMulticast,Reliable)
	virtual void MulticastHandleDeath();

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeLine(UMaterialInstanceDynamic* MaterialInstanceDynamic);
	UFUNCTION(BlueprintImplementableEvent)
	void WeaponStartDissolveTimeLine(UMaterialInstanceDynamic* WeaponMaterialInstanceDynamic);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
private:
	UPROPERTY(EditAnywhere,Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere,Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
