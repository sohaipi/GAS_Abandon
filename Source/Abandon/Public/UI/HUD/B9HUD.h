// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "B9HUD.generated.h"

struct FWidgetControllerParams;
class UB9OverlayWidgetController;
class UB9UserWidget;
/**
 * 
 */
UCLASS()
class ABANDON_API AB9HUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UB9UserWidget> OverlayWidget;

	//初始化用于显示的HUD组件
	UB9OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UB9OverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UB9OverlayWidgetController> OverlayWidgetControllerClass;

};
