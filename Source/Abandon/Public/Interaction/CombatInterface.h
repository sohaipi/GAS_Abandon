// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag MontageTag;
};



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

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetCombatTipLocation(const FGameplayTag& GameplayTag);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateWarpingTarget(const FVector& Target);

	//蓝图引用声明则无法在C++中覆写，故使用此声明，既可以在C中覆写，又可以在蓝图中引用，会自动生成一个虚拟版本以在C中覆写。
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetCombatTarget(AActor* InCombatTarget);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor* GetCombatTarget() const;
	
	virtual void Die() = 0;
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool IsDead() const;
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor* GetAvatar() ;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontages();
};
