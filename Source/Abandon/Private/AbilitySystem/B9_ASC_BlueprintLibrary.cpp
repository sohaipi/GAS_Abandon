// Copyright M9Only


#include "AbilitySystem/B9_ASC_BlueprintLibrary.h"

#include "AbilitySystemComponent.h"
#include "B9AbilitySystemTypes.h"
#include "Game/B9GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/B9PlayerState.h"
#include "AbilitySystem/Data/B9CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"
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
	UB9CharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
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

void UB9_ASC_BlueprintLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass)
{
	UB9CharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& EnemyClassDefaultInfo = CharacterClassInfo->FindCharacterClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> Ability:EnemyClassDefaultInfo.StartUpAbilities)
	{
		
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);	
		}
		
	}
}

UB9CharacterClassInfo* UB9_ASC_BlueprintLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AB9GameModeBase* GameModeBase = Cast<AB9GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameModeBase == nullptr) return nullptr;

	return  GameModeBase->CharacterClassInfo;
}

bool UB9_ASC_BlueprintLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FB9GameplayEffectContext* B9EffectContext = static_cast<const FB9GameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return B9EffectContext->IsBlockedHit();
	}
	return false;
}

bool UB9_ASC_BlueprintLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FB9GameplayEffectContext* B9EffectContext = static_cast<const FB9GameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return B9EffectContext->IsCriticalHit();
	}
	return false;
}

void UB9_ASC_BlueprintLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FB9GameplayEffectContext* B9EffectContext = static_cast<FB9GameplayEffectContext*>(EffectContextHandle.Get()))
	{
		B9EffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UB9_ASC_BlueprintLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FB9GameplayEffectContext* B9EffectContext = static_cast<FB9GameplayEffectContext*>(EffectContextHandle.Get()))
	{
		B9EffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
