#include "FSM/FSMComponent.h"

#include "FSM/FSMBaseAsset.h"
#include "FSM/StateBase.h"

void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	if(ActiveFSM) SetNextSate(ActiveFSM->InitialState);
}

void UFSMComponent::SetNextSate(TSubclassOf<UStateBase> InNextSate)
{
	if(!ActiveState && ActiveFSM->FSM.Contains(ActiveState->GetClass()))
	{
		const FStateConditionEvalExpr& Cond = ActiveFSM->FSM[ActiveState->GetClass()];

		FTransitionCollection Transitions = Cond.AvailableStates[InNextSate];

		for(UClass* TransitionClass : Transitions)
		{
			
		}
	}
}

void UFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UFSMComponent::IsStateAvailable(TSubclassOf<UStateBase> InQueriedState)
{
	return false;
}

