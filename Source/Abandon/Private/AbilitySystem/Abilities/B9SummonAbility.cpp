// Copyright M9Only


#include "AbilitySystem/Abilities/B9SummonAbility.h"

TArray<FVector> UB9SummonAbility::GetSpawnLocation()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location =  GetAvatarActorFromActorInfo()->GetActorLocation();

	
	return FVector();
}
