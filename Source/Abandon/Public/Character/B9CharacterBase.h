// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "B9CharacterBase.generated.h"

class UNiagaraSystem;
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

	/* 战斗接口 */
	//只在服务器处理一些内容；
	virtual void Die() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual FVector GetCombatTipLocation_Implementation(const FGameplayTag& GameplayTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	/* 战斗接口 */

	UPROPERTY(EditAnywhere,Category = "Combat")
	TArray<FTaggedMontage> AttackMontages;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat" )
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandSocketName;
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;
	
	bool bDead = false;
	
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

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UNiagaraSystem* BloodEffect;
private:
	UPROPERTY(EditAnywhere,Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere,Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
