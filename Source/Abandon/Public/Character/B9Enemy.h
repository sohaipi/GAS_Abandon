// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "Character/B9CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "B9Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ABANDON_API AB9Enemy : public AB9CharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
public:
	AB9Enemy();
	virtual void BeginPlay() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlight=false;
};
