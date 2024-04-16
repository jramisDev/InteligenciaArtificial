#include "FSM/StateBase.h"

#include "GameFramework/Character.h"

void UStateBase::InitState_Implementation(AActor* InSourceActor)
{
	StateOwner = InSourceActor;
}

void UStateBase::TickState_Implementation(float DeltaSeconds)
{
}

void UStateBase::FinishState_Implementation(EFinishStateReason InFinishedReason)
{
}
