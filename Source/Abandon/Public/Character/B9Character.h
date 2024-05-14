// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Character/B9CharacterBase.h"
#include "B9Character.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API AB9Character : public AB9CharacterBase
{
	GENERATED_BODY()

public:
	AB9Character();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;
};
