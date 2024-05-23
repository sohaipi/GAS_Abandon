// Copyright M9Only


#include "Input/B9InputConfig.h"

const UInputAction* UB9InputConfig::FindInputActionForTag(const FGameplayTag InputTag,bool bLogNotFound )const
{
	for (FB9InputActionWithTag Action:B9AbilityInputAction )
	{
		if (Action.InputAction && Action.InputTag  == InputTag)
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't find AbilityInputAction for TAG: [%s], on InputConfig: [%s]"),*InputTag.ToString(),*GetNameSafe(this));
	}
	return nullptr;
}
