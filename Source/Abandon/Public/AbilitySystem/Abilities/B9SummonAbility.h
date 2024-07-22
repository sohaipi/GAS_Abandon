// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/B9GameplayAbility.h"
#include "B9SummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API UB9SummonAbility : public UB9GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocation();

	UPROPERTY(EditAnywhere,Category = "Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditAnywhere,Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditAnywhere,Category = "Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditAnywhere,Category = "Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditAnywhere,Category = "Summoning")
	float SpawnSpread = 90.f;
};
