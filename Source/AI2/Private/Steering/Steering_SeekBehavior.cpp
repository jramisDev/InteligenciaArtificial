#include "Steering/Steering_SeekBehavior.h"

#include "GameFramework/Character.h"

FVector USteering_SeekBehavior::GetDesiredVelocity_Implementation(float DeltaSeconds) const
{
	ensure(Character);
	
	FVector Direction = GetDestination(DeltaSeconds) - Character->GetActorLocation();
	Direction.Normalize();

	return Direction * GetMaxVelocity();
}

FVector USteering_SeekBehavior::GetSteering_Implementation(float DeltaSeconds) const
{
	ensure(Character);
	
	FVector SteerDirection = GetDesiredVelocity(DeltaSeconds) - GetCurrentVelocity();
	SteerDirection.Normalize();

	return SteerDirection * GetMaxAcceleration();
	
}

FVector USteering_SeekBehavior::GetDestination_Implementation(float DeltaSeconds) const
{
	return Target->GetActorLocation();
}
