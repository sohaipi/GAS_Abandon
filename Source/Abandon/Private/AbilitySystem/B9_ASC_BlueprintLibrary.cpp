// Copyright M9Only


#include "AbilitySystem/B9_ASC_BlueprintLibrary.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/B9PlayerState.h"
#include "UI/HUD/B9HUD.h"
#include "UI/WidgetController/B9WidgetController.h"

UB9OverlayWidgetController* UB9_ASC_BlueprintLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC =  UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AB9HUD* B9HUD = Cast<AB9HUD>(PC->GetHUD()))
		{
			AB9PlayerState* PS = PC->GetPlayerState<AB9PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			
			return  B9HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UB9AttributeMenuWidgetController* UB9_ASC_BlueprintLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC =  UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AB9HUD* B9HUD = Cast<AB9HUD>(PC->GetHUD()))
		{
			AB9PlayerState* PS = PC->GetPlayerState<AB9PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			
			return B9HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
