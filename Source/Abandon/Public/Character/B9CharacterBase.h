// Copyright M9Only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "B9CharacterBase.generated.h"

UCLASS(Abstract)
//添加abstract使该类不可被拖入关卡；
class ABANDON_API AB9CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AB9CharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat" )
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
