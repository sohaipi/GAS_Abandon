// Copyright M9Only


#include "Player/B9PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Input/B9InputComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/B9AbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "B9GameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Interaction/EnemyInterface.h"

AB9PlayerController::AB9PlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AB9PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(B9Context);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(B9Context, 3);
	
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
	B9InputComponent->BindAction(LShiftAction,ETriggerEvent::Started,this,&AB9PlayerController::LShiftPressed);
	B9InputComponent->BindAction(LShiftAction,ETriggerEvent::Completed,this,&AB9PlayerController::LShiftReleased);

	B9InputComponent->BindAbilityActions(B9InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

void AB9PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}
void AB9PlayerController::AutoRun()
{
	if (bAutoRunning == false) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocMoveTo = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector DierMoveTo = Spline->FindDirectionClosestToWorldLocation(LocMoveTo,ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(DierMoveTo);

		const float DistanceToDestination = (LocMoveTo - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}


void AB9PlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);	
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor) 
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

void AB9PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	/*GEngine->AddOnScreenDebugMessage(1,3.F,FColor::Black,*InputTag.ToString());*/
	if (InputTag.MatchesTagExact(FB9GameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AB9PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FB9GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	
	if (!bTargeting && !bLShiftKeyDown)
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			//导航组件函数库
			if (UNavigationPath* Path= UNavigationSystemV1::FindPathToLocationSynchronously(
				this,ControlledPawn->GetActorLocation(),CachedDestination))
			{
				for (const FVector& PointLoc: Path->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(),PointLoc,20.f,8,FColor::Blue,false,50.f);
				}
				CachedDestination = Path->PathPoints[Path->PathPoints.Num()-1];
				bAutoRunning = true;
			}
		}
	}
		bTargeting = false;
		FollowTime = 0.f;
}

void AB9PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FB9GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
			GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	if (bTargeting || bLShiftKeyDown)
	{
		if (GetASC())
			GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
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


