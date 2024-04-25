#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "UObject/Object.h"
#include "MoveToState.generated.h"

UCLASS()
class AI2_API UMoveToState : public UStateBase
{
	GENERATED_BODY()

protected:
	
	virtual void InitState_Implementation(AActor* InSourceActor) override;
	virtual void FinishState_Implementation(EFinishStateReason InFinishedReason) override;
	virtual void TickState_Implementation(float DeltaSeconds) override;
};
