// Copyright M9Only


#include "AbilitySystem/Abilities/B9SummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UB9SummonAbility::GetSpawnLocation()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location =  GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;
	
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread/2,FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i= 0 ; i < NumMinions ; i++)
	{
		const FVector Direction =  LeftOfSpread.RotateAngleAxis(DeltaSpread * i,FVector::UpVector);
		FVector PreSpawnLocation =  Location + Direction * FMath::RandRange(MinSpawnDistance,MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult,PreSpawnLocation+ FVector(0.f,0.f,500.f), PreSpawnLocation + FVector(0.f,0.f,-500.f),ECC_WorldStatic);
		if (HitResult.bBlockingHit)
		{
			PreSpawnLocation = HitResult.ImpactPoint;
		}
		/*UKismetSystemLibrary::DrawDebugSphere(GetWorld(),PreSpawnLocation,15,12,FLinearColor::Red,2,1);*/
		SpawnLocations.Add(PreSpawnLocation);
	}
	
	return SpawnLocations;
}

TSubclassOf<APawn> UB9SummonAbility::GetRandomMinionClass()
{
	int32 Index = FMath::RandRange(0 , MinionClasses.Num()-1 );
	return MinionClasses[Index];
}
