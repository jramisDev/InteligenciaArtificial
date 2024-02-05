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

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}
