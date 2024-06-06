// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "B9GameModeBase.generated.h"

class UB9CharacterClassInfo;
/**
 * 
 */
UCLASS()
class ABANDON_API AB9GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category = "Character Class Default")
	TObjectPtr<UB9CharacterClassInfo> CharacterClassInfo;
};
