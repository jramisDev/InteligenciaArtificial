#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

UCLASS()
class AI2_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	void SetMoveCommand(const FVector& InGoal);
	
protected:
	virtual void BeginPlay() override;

	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
	void MoveFinished(FAIRequestID FaiRequestID, const FPathFollowingResult& PathFollowingResult);

};
