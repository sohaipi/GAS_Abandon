// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "B9InputConfig.generated.h"

struct FGameplayTag;
class UInputAction;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FB9InputActionWithTag
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
	
};

UCLASS()
class ABANDON_API UB9InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindInputActionForTag(FGameplayTag InputTag, bool bLogNotFound = false)const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FB9InputActionWithTag> B9AbilityInputAction;
};
