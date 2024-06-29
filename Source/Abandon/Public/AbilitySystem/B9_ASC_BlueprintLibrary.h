// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/B9CharacterClassInfo.h"
#include "B9_ASC_BlueprintLibrary.generated.h"

struct FGameplayEffectContextHandle;
class UB9AttributeMenuWidgetController;
class UB9OverlayWidgetController;
/**
 * 
 */
UCLASS()
class ABANDON_API UB9_ASC_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure,Category = "B9_ASC_BlueprintLibrary|WidgetController")
	static UB9OverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	
	UFUNCTION(BlueprintPure,Category = "B9_ASC_BlueprintLibrary|WidgetController")
	static UB9AttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable,Category = "B9_ASC_BlueprintLibrary|CharacterDefault")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass,float Level,UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintCallable,Category = "B9_ASC_BlueprintLibrary|CharacterDefault")
	static void GiveStartupAbilities(const UObject* WorldContextObject,UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable,Category = "B9_ASC_BlueprintLibrary|CharacterDefault")
	static UB9CharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,Category = "B9_ASC_BlueprintLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure,Category = "B9_ASC_BlueprintLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable,Category = "B9_ASC_BlueprintLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,bool bInIsBlockedHit);
	UFUNCTION(BlueprintCallable,Category = "B9_ASC_BlueprintLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,bool bInIsCriticalHit);
};
