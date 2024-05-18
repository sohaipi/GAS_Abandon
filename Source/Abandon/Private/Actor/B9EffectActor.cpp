// Copyright M9Only


#include "Actor/B9EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "AbilitySystem/B9AttributeSet.h"


AB9EffectActor::AB9EffectActor()
{

	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot")) ;


	
	//Debug
	/*StaticMesh= CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());*/
}

//Debug用重叠事件
/*void AB9EffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	//强制转换了静态变量，用于临时测试数值变换, 需用正式的GameplayEffect实现。
	if (IAbilitySystemInterface* AscInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UB9AttributeSet* B9AttributeSet = Cast<UB9AttributeSet>(AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UAttributeSet::StaticClass()));
		UB9AttributeSet* B9AttributeSetMutable = const_cast<UB9AttributeSet*>(B9AttributeSet);
		B9AttributeSetMutable->SetHealth(B9AttributeSetMutable->GetHealth() + 25.f);
		B9AttributeSetMutable->SetMana(B9AttributeSetMutable->GetMana() + 25.f);
		Destroy();
	}
}

void AB9EffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}*/

void AB9EffectActor::BeginPlay()
{
	Super::BeginPlay();

	
	//Debug
	/*Sphere->OnComponentBeginOverlap.AddDynamic(this,&AB9EffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AB9EffectActor::OnEndOverlap);*/
}

//一并封装对effect的应用与移除的预处理
void AB9EffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//需实现接口的声明版本
	/*IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target);
	if (ASCInterface)
	{
		ASCInterface->GetAbilitySystemComponent();
	}*/
	
	//库函数检查ACTOR是否拥有ASC，没有则返回nullptr，不需接口实现。
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle =  TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =  TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel,EffectContextHandle);
	//通过*将get到的原始指针转换为引用。保存在数组以供移除。
	const FActiveGameplayEffectHandle ActiveEffectHandle= TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//~
	const bool bIsInfinite =  EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
}

void AB9EffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if ((InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap))
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AB9EffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	//因为只有这种效果会有移除的需要，所以直接写在里面移除。
	if (InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		//不能在循环中删除MAP中的元素，用数组暂存起来。
		TArray<FActiveGameplayEffectHandle> HandlsToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair:ActiveEffectHandles)
		{
			if(TargetASC == HandlePair.Value)
			{
				//实际移除Effect
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1.f);
				HandlsToRemove.Add(HandlePair.Key);
			}
		}
		for(FActiveGameplayEffectHandle& Handle:HandlsToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

