#include "AI/NPCBase.h"

#include "NiagaraComponent.h"
#include "AI/AIControllerBase.h"

ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControllerBase::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// NiagaraNPCSelected = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSelected"));
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
