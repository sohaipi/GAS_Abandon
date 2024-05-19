// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "B9AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FB9AttributeInformation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();
	
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * 
 */
UCLASS()
class ABANDON_API UB9AttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FB9AttributeInformation FindAttributeInfoForTag(const FGameplayTag& AttributeTag,bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FB9AttributeInformation>B9AttributeInformation;
};
