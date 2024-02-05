// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/AI2PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AI/NPCBase.h"
#include "UI/HUD_RTS.h"

AAI2PlayerController::AAI2PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AAI2PlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(RTSMappingContext, 0);
	}

	HudRTS = Cast<AHUD_RTS>(GetHUD());
}

void AAI2PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AAI2PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AAI2PlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AAI2PlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AAI2PlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AAI2PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AAI2PlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AAI2PlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AAI2PlayerController::OnTouchReleased);

		//RTS inputs
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &AAI2PlayerController::SelectNPC);
		//EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &AAI2PlayerController::SelectedBoxNPC);
		//EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &AAI2PlayerController::DeSelectedBoxNPC);
		
		EnhancedInputComponent->BindAction(OrderAction, ETriggerEvent::Started, this, &AAI2PlayerController::OrderNPC);



		
	}
}

void AAI2PlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AAI2PlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AAI2PlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AAI2PlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AAI2PlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AAI2PlayerController::SelectNPC()
{

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("SelectNPC!"));
	
	FHitResult Hit;
	
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, Hit)) return;
	
	if(ANPCBase* NPC = Cast<ANPCBase>(Hit.GetActor()))
	{
		if(!NPCArray.Contains(NPC))
			NPCArray.Add(NPC);
		else
			NPCArray.Remove(NPC);
	}
}

void AAI2PlayerController::SelectedBoxNPC(const FInputActionValue& InputActionValue)
{
	HudRTS->InitialPointSelection = HudRTS->GetMousePos2D();

	// if(HudRTS->bStartSelecting)
	// 	HudRTS->bStartSelecting = false;
	// else	
	// 	HudRTS->bStartSelecting = true;	


	
}

void AAI2PlayerController::DeSelectedBoxNPC()
{
	//HudRTS->bStartSelecting = false;
}

void AAI2PlayerController::OrderNPC()
{
	FHitResult Hit;
	
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit)) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,
		FXCursor,
		Hit.Location,
		FRotator::ZeroRotator,
		FVector(1.f, 1.f, 1.f),
		true,
		true,
		ENCPoolMethod::None,
		true);
	
	for(ANPCBase* NPC : NPCArray)
	{
		if(AAIControllerBase* Controller = Cast<AAIControllerBase>(NPC->GetController()))
		{
			Controller->SetMoveCommand(Hit.Location, true);
		}
	}
}
