// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "B9AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API UB9AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UB9AssetManager& Get();

protected:
	virtual void StartInitialLoading() override;

private:
};
