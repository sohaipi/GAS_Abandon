// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "B9PlayerController.generated.h"


class UDamageTextComponent;
class USplineComponent;
struct FGameplayTag;
class UB9InputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UB9AbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ABANDON_API AB9PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AB9PlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	//只需在当事客户端执行;
	UFUNCTION(Client,Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter,bool bBlockedHit,bool bCriticalHit);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> B9Context;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LShiftAction;

	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();
	FHitResult CursorHit;
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void LShiftPressed() { bLShiftKeyDown = true;}; 
	void LShiftReleased(){ bLShiftKeyDown = false;};
	bool bLShiftKeyDown;
	
	UPROPERTY(EditDefaultsOnly,Category  = "Input")
	TObjectPtr<UB9InputConfig> B9InputConfig;

	UPROPERTY()
	TObjectPtr<UB9AbilitySystemComponent> B9AbilitySystemComponent;

	UB9AbilitySystemComponent* GetASC();

	//移动部分
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();


	UPROPERTY(EditDefaultsOnly,Category = "DamageText")
	TSubclassOf<UDamageTextComponent> DamageTextCompClass;
};
