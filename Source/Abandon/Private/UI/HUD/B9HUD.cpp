// Copyright M9Only


#include "UI/HUD/B9HUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/B9UserWidget.h"
#include "UI/WidgetController/B9AttributeMenuWidgetController.h"
#include "UI/WidgetController/B9OverlayWidgetController.h"

UB9OverlayWidgetController* AB9HUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UB9OverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UB9AttributeMenuWidgetController* AB9HUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if(AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UB9AttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

void AB9HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass MISS, ERROR"));
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass MISS,ERROR"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UB9UserWidget>(Widget);
		
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UB9OverlayWidgetController* WidgetController =  GetOverlayWidgetController(WidgetControllerParams);
	
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitValues();
	
	Widget->AddToViewport();
}


