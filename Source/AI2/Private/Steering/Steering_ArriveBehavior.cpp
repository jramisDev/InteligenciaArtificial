#include "Steering/Steering_ArriveBehavior.h"

#include "GameFramework/Character.h"

FVector USteering_ArriveBehavior::GetDesiredVelocity_Implementation() const
{

	FVector CurrentDesiredVelocity = Super::GetDesiredVelocity_Implementation();

	const float Distance = FVector::Distance(Character->GetActorLocation(), GetDestination());
	
	if(Distance < DistanceThreshold)
	{
		CurrentDesiredVelocity *= Distance / DistanceThreshold;
	}
	
	return CurrentDesiredVelocity;
}

void USteering_ArriveBehavior::DrawDebugMovementComponents(float DeltaSeconds)
{
	Super::DrawDebugMovementComponents(DeltaSeconds);

	//DrawDebugCircle(Character->GetWorld(), Destination, DistanceThreshold, 10.f, FColor::Green, false, DeltaSeconds, 0, 100.f, FVector::ForwardVector, FVector::UpVector);
}
