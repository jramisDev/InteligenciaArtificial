#include "FSM/FSMComponent.h"

#include "AudioDevice.h"
#include "FSM/FSMBaseAsset.h"
#include "FSM/StateBase.h"
#include "FSM/TransitionBase.h"

UFSMComponent::UFSMComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	if(ActiveFSM && !ActiveState)
	{
		SetNewState(ActiveFSM->InitialState);
	}
}

void UFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ActiveState) ActiveState->TickState(DeltaTime);

#if WITH_EDITOR
	ShowDebugStateMachine(DeltaTime);
#endif
	
	
}

void UFSMComponent::SetNewState(TSubclassOf<UStateBase> InNextSate)
{
	//ActiveState->MarkAsGarbage();
	ActiveState = NewObject<UStateBase>(this, InNextSate);
	ActiveState->InitState(GetOwner());
}

#if WITH_EDITOR
void UFSMComponent::ShowDebugStateMachine(float DeltaTime) const
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, DeltaTime, FColor::Red, TEXT("FSM DEBUG INFO"));	

		if(ActiveState)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, DeltaTime, FColor::Red, FString::Printf(TEXT("Current State: %s"), *ActiveState->GetName()));

			FString StateInfo;
			ActiveState->GetStateDebugInfo(StateInfo);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, DeltaTime, FColor::Red, FString::Printf(TEXT("State Info: %s"), *StateInfo));
			
		}else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, DeltaTime, FColor::Red, TEXT("No active state"));	
		}
	} 
}
#endif

void UFSMComponent::SetNextSate(TSubclassOf<UStateBase> InNextSate)
{
	if(ActiveState && IsStateAvailable(InNextSate))
	{
		ActiveState->FinishState(EFinishStateReason::SuccessFinished);

		SetNewState(InNextSate);
	}
}

bool UFSMComponent::IsStateAvailable(TSubclassOf<UStateBase> InQueriedState)
{
	if(ActiveFSM->FSM.Contains(ActiveState->GetClass()))
	{
		const FStateConditionEvalExpr& ConditionEvalExpr = ActiveFSM->FSM[ActiveState->GetClass()];
	
		FTransitionCollection TransitionCollection = ConditionEvalExpr.AvailableStates[InQueriedState];
		for(const UClass* TransitionClass : TransitionCollection.Transitions)
		{
			if(!TransitionClass->GetDefaultObject<UTransitionBase>()->CheckCondition(GetOwner()))
			{
				return false;
			}
		}
	}

	return true;
}

