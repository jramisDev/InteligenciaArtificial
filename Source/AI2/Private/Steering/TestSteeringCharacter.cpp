#include "Steering/TestSteeringCharacter.h"

#include "AI/AIControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	GetCharacterMovement()->Velocity = GetActorForwardVector() * GetCharacterMovement()->GetMaxSpeed();

	if(CurrentSteeringBehavior && TargetActor)
	{
		CurrentSteeringBehavior->Init(this, TargetActor);
	}
	
}

#if WITH_EDITOR
void ATestSteeringCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ATestSteeringCharacter, InitialSteeringClass))
	{
		if(CurrentSteeringBehavior)
		{
			CurrentSteeringBehavior->MarkAsGarbage();
		}
	}
	if(InitialSteeringClass)
	{
		CurrentSteeringBehavior = NewObject<USteeringCustom>(this, InitialSteeringClass);
	}
	
}
#endif

void ATestSteeringCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestSteeringCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

