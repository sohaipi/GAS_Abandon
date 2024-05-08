// Copyright M9Only


#include "Actor/B9EffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/B9AttributeSet.h"


AB9EffectActor::AB9EffectActor()
{

	PrimaryActorTick.bCanEverTick = false;

	StaticMesh= CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AB9EffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	//强制转换了静态变量，用于临时测试数值变换, 需用正式的GameplayEffect实现。
	if (IAbilitySystemInterface* AscInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UB9AttributeSet* B9AttributeSet = Cast<UB9AttributeSet>(AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UAttributeSet::StaticClass()));
		UB9AttributeSet* B9AttributeSetMutable = const_cast<UB9AttributeSet*>(B9AttributeSet);
		B9AttributeSetMutable->SetHealth(B9AttributeSetMutable->GetHealth() + 25.f);
		Destroy();
	}
}

void AB9EffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AB9EffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AB9EffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AB9EffectActor::OnEndOverlap);
}

