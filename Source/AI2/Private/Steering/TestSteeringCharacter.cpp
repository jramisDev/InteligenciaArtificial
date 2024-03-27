#include "Steering/TestSteeringCharacter.h"

#include "AI/AIControllerBase.h"
#include "Steering/SteeringCustom.h"


ATestSteeringCharacter::ATestSteeringCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControllerBase::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
}

void ATestSteeringCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentSteeringBehavior = NewObject<USteeringCustom>(this, InitialSteeringClass);

	if(CurrentSteeringBehavior && ReferenceDestination)
	{
		CurrentSteeringBehavior->SetAgent(this);
		CurrentSteeringBehavior->SetDestination(ReferenceDestination->GetActorLocation());
	}

	AddMovementInput(FVector::ForwardVector * 100.f);
	
}

void ATestSteeringCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentSteeringBehavior)
	{
		CurrentSteeringBehavior->TicketSteering(DeltaTime);
	}
}

void ATestSteeringCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

