// Copyright M9Only


#include "Player/B9PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Input/B9InputComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "Interaction/EnemyInterface.h"

AB9PlayerController::AB9PlayerController()
{
	bReplicates = true;
}

void AB9PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(B9Context);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(B9Context, 3);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AB9PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UB9InputComponent* B9InputComponent = CastChecked<UB9InputComponent>(InputComponent);
	B9InputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AB9PlayerController::Move);

	B9InputComponent->BindAbilityActions(B9InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

void AB9PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AB9PlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	//判断上一帧与这一帧检测所可能出现的五种不同的结果并处理之。

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else
		{
			if (ThisActor != LastActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}

void AB9PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	/*GEngine->AddOnScreenDebugMessage(1,3.F,FColor::Black,*InputTag.ToString());*/
}

void AB9PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AB9PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UB9AbilitySystemComponent* AB9PlayerController::GetASC()
{
	if (B9AbilitySystemComponent == nullptr)
	{
		B9AbilitySystemComponent =Cast<UB9AbilitySystemComponent>
								(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>())) ;
	}
	return B9AbilitySystemComponent;	
}
	

void AB9PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation  (0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}


