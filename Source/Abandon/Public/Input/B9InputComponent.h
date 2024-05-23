// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "B9InputConfig.h"
#include "EnhancedInputComponent.h"
#include "B9InputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API UB9InputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType,typename HeldFuncType>
	void BindAbilityActions(const UB9InputConfig* InputConfig,UserClass* Object, PressedFuncType PressFunc,ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc); 
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UB9InputComponent::BindAbilityActions(const UB9InputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FB9InputActionWithTag& Action: InputConfig->B9AbilityInputAction)
	{
		if (Action.InputAction &&  Action.InputTag.IsValid())
		{
			if (PressFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressFunc,Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			if (HeldFunc)
			{
				//Triggered每帧检测，BindAction 中 heldFunc后多余的参数传给回调heldFunc
				BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
		}
	}
}

