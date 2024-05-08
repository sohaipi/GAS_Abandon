// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "B9UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API UB9UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
