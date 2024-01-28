#include "AI/AIControllerBase.h"

#include "AI/NPCBase.h"
#include "Navigation/PathFollowingComponent.h"

AAIControllerBase::AAIControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIControllerBase::SetMoveCommand(const FVector& InGoal)
{
	if(GetCharacter())
	{
		FAIMoveRequest MoveRequest;
		MoveRequest
			.SetAcceptanceRadius(50.f)
			.SetCanStrafe(true)
			.SetUsePathfinding(true)
			.SetGoalLocation(InGoal);

		FNavPathSharedPtr Path;

		FPathFollowingRequestResult RequestID = MoveTo(MoveRequest, &Path);

		GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ThisClass::MoveFinished);
	}
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AAIControllerBase::OnUnPossess()
{
	Super::OnUnPossess();
}

void AAIControllerBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if(Result.IsSuccess())
	{
		
	}else if (Result.IsFailure())
	{
		
	}else if(Result.IsInterrupted())
	{
		
	}
}

void AAIControllerBase::MoveFinished(FAIRequestID FaiRequestID, const FPathFollowingResult& PathFollowingResult)
{

		GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
		
	
}
