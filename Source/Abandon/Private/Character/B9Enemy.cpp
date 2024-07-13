// Copyright M9Only


#include "Character/B9Enemy.h"

#include "Abandon/Abandon.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "AbilitySystem/B9AttributeSet.h"
#include "AbilitySystem/B9_ASC_BlueprintLibrary.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/B9UserWidget.h"
#include "B9GameplayTags.h"
#include "AI/B9AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/B9AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AB9Enemy::AB9Enemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UB9AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//Gameplay Effects are not replicated.Gameplay Cues and Gameplay Tags replicated to all clients.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UB9AttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AB9Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	B9AIController = Cast<AB9AIController>(NewController);
	
	B9AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	B9AIController->RunBehaviorTree(BehaviorTree);
	B9AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"),false);

	B9AIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),CharacterClass != ECharacterClass::Warrior);

}

void AB9Enemy::BeginPlay()
{
	//由于挂在PAWN上，所以只需简单得在beginplay上做ASC的初始化；
	Super::BeginPlay();

	//只在服务器上，不然客户端没GameMode会空指针崩溃；
	if (HasAuthority()) { InitAbilityActorInfo(); }
	
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	UB9_ASC_BlueprintLibrary::GiveStartupAbilities(this,AbilitySystemComponent,CharacterClass);

	if (UB9UserWidget* UserWidget = Cast<UB9UserWidget>(HealthBar->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);		
	}

	if (const UB9AttributeSet* B9AttributeSet = Cast<class UB9AttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				B9AttributeSet->GetHealthAttribute()).AddLambda(
					[this](const FOnAttributeChangeData& Data)
					{OnHealthChanged.Broadcast(Data.NewValue);}
				);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				B9AttributeSet->GetMaxHealthAttribute()).AddLambda(
					[this](const FOnAttributeChangeData& Data)
					{OnMaxHealthChanged.Broadcast(Data.NewValue);}
				);
		//Allow events to be registered for specific gameplay tags being added or removed
		AbilitySystemComponent->RegisterGameplayTagEvent(FB9GameplayTags::Get().Effect_Ability_HitReact,EGameplayTagEventType::NewOrRemoved).AddUObject(
				this,&AB9Enemy::HitReactOnDamage);
	
		OnHealthChanged.Broadcast(B9AttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(B9AttributeSet->GetMaxHealth());
	}
	
}

void AB9Enemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AB9Enemy::UnHighlightActor() 
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AB9Enemy::GetPlayerLevel()
{
	return Level;
}

void AB9Enemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AB9Enemy::HitReactOnDamage(const FGameplayTag Tag, int32 TagCount)
{
	bHitReacting = TagCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	B9AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"),bHitReacting );
}

void AB9Enemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UB9AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())	{InitDefaultAttribute(); }
}

void AB9Enemy::InitDefaultAttribute() const
{
	UB9_ASC_BlueprintLibrary::InitializeDefaultAttributes(this,CharacterClass,Level,AbilitySystemComponent);
}
