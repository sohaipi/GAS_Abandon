// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "B9HUD.generated.h"



class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UB9OverlayWidgetController;
class UB9UserWidget;
class UB9AttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class ABANDON_API AB9HUD : public AHUD
{
	GENERATED_BODY()
public:
	
	//初始化用于显示的HUD组件，保证只有一个overlay控制器；
	UB9OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UB9AttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);
	
protected:

	
private:
	UPROPERTY()
	TObjectPtr<UB9UserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UB9OverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UB9OverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UB9AttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UB9AttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

};
