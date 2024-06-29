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

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
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
template<>
	struct TStructOpsTypeTraits< FB9GameplayEffectContext > : public TStructOpsTypeTraitsBase2< FB9GameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};