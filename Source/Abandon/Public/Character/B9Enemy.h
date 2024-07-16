// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Character/B9CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/B9OverlayWidgetController.h"
#include "AbilitySystem/Data/B9CharacterClassInfo.h"
#include "B9Enemy.generated.h"

class UBehaviorTree;
class AB9AIController;
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
	virtual void PossessedBy(AController* NewController) override;
	// Enemy Interface **
	virtual void BeginPlay() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// Enemy Interface **

	// Combat Interface **
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
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

	UPROPERTY(BlueprintReadWrite,Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	AActor* GetCombatTarget_Implementation() const override;
	
protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttribute() const;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	int32 Level = 1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category ="Combat")
	float BaseWalkSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category ="Combat")
	float LifeSpan = 5.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY()
	TObjectPtr<AB9AIController> B9AIController;
};
