// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "B9_ASC_BlueprintLibrary.generated.h"

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
	
};
