#include "FSM/MoveToState.h"

#include "AI/AIControllerBase.h"
#include "FSM/BlackboardFSM.h"
#include "FSM/FSMComponent.h"

void UMoveToState::InitState_Implementation(AActor* InSourceActor)
{
	Super::InitState_Implementation(InSourceActor);

	if(const UFSMComponent* FsmComp = InSourceActor->FindComponentByClass<UFSMComponent>())
	{
		AActor* Player = FsmComp->BlackboardFsm->GetValueFromProperty_Actor(TEXT("Player"));
		if(!Player) return;
		
		if(const APawn* Pawn = Cast<APawn>(InSourceActor))
		{
			if(AAIControllerBase*  Controller = Cast<AAIControllerBase>(Pawn->GetController()))
			{
				Controller->MoveToActor(Player);
			}}
		}
	}
	
}
