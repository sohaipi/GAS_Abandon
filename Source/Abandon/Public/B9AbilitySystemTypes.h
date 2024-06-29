#pragma once


#include "GameplayEffectTypes.h"
#include "B9AbilitySystemTypes.generated.h"

//自定义GE上下文内容，增加一些标志位等等，如是否暴击...
USTRUCT(BlueprintType)
struct FB9GameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	//来自分类，用于返回给反射系统；
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}
	//网络同步序列化
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	bool IsBlockedHit() const { return bIsBlockedHit;}
	bool IsCriticalHit() const { return  bIsCriticalHit;}

	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit;}
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit;}
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;
	UPROPERTY()
	bool bIsCriticalHit = false;
};