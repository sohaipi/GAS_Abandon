// Copyright M9Only


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreatTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		//在服务器运行，监听targetdata;ASC带的函数。
		//active执行时，运行等待targetdata;
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(
			SpecHandle,ActivationPredictionKey).AddUObject(this,&UTargetDataUnderMouse::onTargetDataReplicatedCallback);
		//targetdata先到而activate()后执行的情况。完成时返回真
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle,ActivationPredictionKey);
		//等待数据到达
		if (bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

//TargetData是一个特有的概念，用于解决在同步过程中的数据与函数执行先后不一致的问题；
void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
 
	//只存一个点击数据的targetdata
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit;
	Data->HitResult = HitResult;
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	//用于发送data到服务端。
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),GetActivationPredictionKey(),
		DataHandle,FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);

	//客户端广播
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(Data);
	}
}

void UTargetDataUnderMouse::onTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data,
	FGameplayTag ActivationTag)
{
	//收到数据后通知清除targetdata
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	//广播下去
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(Data);
	}
}
 