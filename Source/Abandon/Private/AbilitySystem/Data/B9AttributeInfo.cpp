// Copyright M9Only


#include "AbilitySystem/Data/B9AttributeInfo.h"

FB9AttributeInformation UB9AttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const 
{
	for (const FB9AttributeInformation& Info: B9AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("在AttributeInfo [%s] 中查询不到相关Tag：[%s] "),*GetNameSafe(this),*AttributeTag.ToString());
	}
	return FB9AttributeInformation();
}
