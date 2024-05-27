// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "B9Projectile.generated.h"

class USphereComponent;

UCLASS()
class ABANDON_API AB9Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AB9Projectile();
	UPROPERTY()
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
