#include "AI/NPCBase.h"

#include "AI/AIControllerBase.h"
#include "AI/PatrolComponent.h"

ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControllerBase::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//PatrolComponent = CreateDefaultSubobject<UPatrolComponent>(TEXT("PatrolComponent"));
}

void ANPCBase::StopMovement_Implementation()
{
	if(GetController() && GetController()->Implements<UAIMovementInterface>())
	{
		IAIMovementInterface::Execute_StopMovement(GetController());
	}
}

void ANPCBase::ResumeMovement_Implementation()
{
	if(GetController() && GetController()->Implements<UAIMovementInterface>())
	{
		IAIMovementInterface::Execute_ResumeMovement(GetController());
	}
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	// if(PatrolComponentClass)
	// {
	// 	PatrolComponent = NewObject<UPatrolComponent>(this, PatrolComponentClass);
	// }
	// else
	// {
	// 	PatrolComponent = NewObject<UPatrolComponent>(this);
	// }
}
