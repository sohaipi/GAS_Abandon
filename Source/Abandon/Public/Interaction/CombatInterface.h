// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABANDON_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();
	virtual FVector GetCombatTipLocation();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateWarpingTarget(const FVector& Target);

	//蓝图引用声明则无法在C++中覆写，故使用此声明，既可以在C中覆写，又可以在蓝图中引用，会自动生成一个虚拟版本以在C中覆写。
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	virtual void Die() = 0;
};
