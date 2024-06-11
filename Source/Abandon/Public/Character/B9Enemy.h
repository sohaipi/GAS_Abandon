// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Character/B9CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/B9OverlayWidgetController.h"
#include "AbilitySystem/Data/B9CharacterClassInfo.h"
#include "B9Enemy.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class ABANDON_API AB9Enemy : public AB9CharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
public:
	AB9Enemy();

	// Enemy Interface **
	virtual void BeginPlay() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// Enemy Interface **

	// Combat Interface **
	virtual int32 GetPlayerLevel() override;
	// Combat Interface **

	UPROPERTY(BlueprintReadOnly)
	bool bHighlight=false;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly)
	bool bHitReacting = false;
	UFUNCTION()
	void HitReactOnDamage(const FGameplayTag Tag,int32 TagCount);
	
protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttribute() const;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	int32 Level = 1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	float BaseWalkSpeed = 100.f;
};
