// Copyright M9Only


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/B9AttributeSet.h"

//声明一个结构，用于保存所有捕获定义。原始结构不加U或F，不暴露给蓝图或生成正文宏；
//名字带Statics意图在函数中声明时使用static,使得调用函数时总是使用同一个实例
struct B9DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	B9DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UB9AttributeSet,Armor,Target,false);
	}
};

static const B9DamageStatics& DamageStatics()
{
	static B9DamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	const FGameplayEffectSpec& GESpec = ExecutionParams.GetOwningSpec();
}
