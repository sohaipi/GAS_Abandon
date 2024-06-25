// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABANDON_API IEnemyInterface
{  
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//纯虚函数；使其变成抽象类；调用方必须重写以下函数否则无法实例化抽象类；
	
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
