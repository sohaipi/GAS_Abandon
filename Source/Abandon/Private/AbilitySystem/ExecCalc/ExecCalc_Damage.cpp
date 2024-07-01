// Copyright M9Only


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "B9AbilitySystemTypes.h"
#include "B9GameplayTags.h"
#include "AbilitySystem/B9AttributeSet.h"
#include "AbilitySystem/B9_ASC_BlueprintLibrary.h"
#include "AbilitySystem/Data/B9CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

//声明一个结构，用于保存所有捕获定义。原始结构不加U或F，不暴露给蓝图或生成正文宏；
//名字带Statics意图在函数中声明时使用static,使得调用函数时总是使用同一个实例
struct B9DamageStatics
{
	//使用宏创建定义和资产;
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	B9DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UB9AttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UB9AttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UB9AttributeSet,ArmorPenetration,Source,true);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UB9AttributeSet,CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UB9AttributeSet,CriticalHitResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UB9AttributeSet,CriticalHitDamage,Source,false);
	}
};

static const B9DamageStatics& DamageStatics()
{
	static B9DamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	//添加到捕获数组
	RelevantAttributesToCapture.Add(B9DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(B9DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(B9DamageStatics().ArmorPenetrationDef);

	RelevantAttributesToCapture.Add(B9DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(B9DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(B9DamageStatics().CriticalHitDamageDef);
}

//计算实体
void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	
	const FGameplayEffectSpec& GESpec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = GESpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = GESpec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	//数值获取；
	float Damage = GESpec.GetSetByCallerMagnitude(FB9GameplayTags::Get().Damage);
	
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance,0.f);
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParameters,TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor,0.f);
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluateParameters,SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration,0.f);

	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,EvaluateParameters,SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance,0.f);
	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,EvaluateParameters,TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance,0.f);
	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,EvaluateParameters,SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage,0.f);  

	const UB9CharacterClassInfo* ClassInfo = UB9_ASC_BlueprintLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"),FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	const FRealCurve* EffectiveArmorCurve = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"),FString());
	const float EffectiveArmorCurveCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	const FRealCurve* CriticalHitResistanceCurve = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"),FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	//block成功减伤一半；
	const bool bBlock = FMath::RandRange(1,100) < TargetBlockChance;

	FGameplayEffectContextHandle EffectContextHandle = GESpec.GetContext();
	UB9_ASC_BlueprintLibrary::SetIsBlockedHit(EffectContextHandle,bBlock);
	
	Damage = bBlock ? Damage/2.f : Damage; 
	//护甲穿透无视目标护甲百分比 
	const float EffectArmor = TargetArmor *= (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;
	Damage *= (100 - EffectArmor * EffectiveArmorCurveCoefficient)/100.f;
	//暴击计算
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient ;
	const bool bCriticalHit = FMath::RandRange(1,100) < EffectiveCriticalHitChance ;
	UB9_ASC_BlueprintLibrary::SetIsCriticalHit(EffectContextHandle,bCriticalHit);
	Damage = bCriticalHit ? 2.f * Damage + SourceCriticalHitDamage : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UB9AttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
