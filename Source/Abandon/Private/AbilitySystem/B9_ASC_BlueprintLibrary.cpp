// Copyright M9Only


#include "AbilitySystem/B9_ASC_BlueprintLibrary.h"

#include "AbilitySystemComponent.h"
#include "Game/B9GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/B9PlayerState.h"
#include "AbilitySystem/Data/B9CharacterClassInfo.h"
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

void UB9_ASC_BlueprintLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent* ASC)
{
	const AB9GameModeBase* GameModeBase = Cast<AB9GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameModeBase == nullptr) return;

	UB9CharacterClassInfo* CharacterClassInfo = GameModeBase->CharacterClassInfo;
	const FCharacterClassDefaultInfo DefaultInfo =  CharacterClassInfo->FindCharacterClassDefaultInfo(CharacterClass);

	AActor* AvatarActor = ASC->GetAvatarActor();
	FGameplayEffectContextHandle PrimaryEffectContextHandle = ASC->MakeEffectContext();
	PrimaryEffectContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryOutgoingSpecHandle = ASC->MakeOutgoingSpec(DefaultInfo.PrimaryAttributes,Level,PrimaryEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryOutgoingSpecHandle.Data.Get());
	FGameplayEffectContextHandle SecondaryEffectContextHandle = ASC->MakeEffectContext();
	SecondaryEffectContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryOutgoingSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,SecondaryEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryOutgoingSpec.Data.Get());
	FGameplayEffectContextHandle VitalEffectContextHandle = ASC->MakeEffectContext();
	VitalEffectContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalOutgoingSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,VitalEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalOutgoingSpec.Data.Get());
}

void UB9_ASC_BlueprintLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	const AB9GameModeBase* GameModeBase = Cast<AB9GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameModeBase == nullptr) return;

	UB9CharacterClassInfo* CharacterClassInfo = GameModeBase->CharacterClassInfo;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
	}
}
