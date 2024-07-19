// Copyright M9Only


#include "Actor/B9Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Abandon/Abandon.h"
#include "AbilitySystem/B9_ASC_BlueprintLibrary.h"
#include "Components/AudioComponent.h"

AB9Projectile::AB9Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 1000.F;
	ProjectileMovementComp->MaxSpeed = 1000.F;
	ProjectileMovementComp->ProjectileGravityScale = 0.F;
}
void AB9Projectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AB9Projectile::OnSphereOverlap);

	LoopingSoundComp = UGameplayStatics::SpawnSoundAttached(LoopingSound,GetRootComponent());
}

void AB9Projectile::Destroyed()
{
	//Destroy 会传到客户端，处理客户端Destroy先到而overlap还没发生的情况。
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		if (LoopingSoundComp) LoopingSoundComp->Stop();
	}
	Super::Destroyed();
	
}

void AB9Projectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DamageEffectSpecHandle.Data.IsValid() || DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor)
	{
		return;
	}
	if (!UB9_ASC_BlueprintLibrary::IsNotFriends(DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser(),OtherActor))
	{
		return;
	}
	if (!bHit)
	{
		if (LoopingSoundComp) LoopingSoundComp->Stop();
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
	}
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

