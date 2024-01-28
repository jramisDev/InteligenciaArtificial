#include "AI/NPCBase.h"
#include "AI/AIControllerBase.h"

ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControllerBase::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;	
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}
