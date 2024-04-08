#include "Steering/Steering_SeekBehavior.h"

#include "GameFramework/Character.h"

FVector USteering_SeekBehavior::GetDesiredVelocity_Implementation() const
{
	ensure(Character);
	
	FVector Direction = GetDestination() - Character->GetActorLocation();
	Direction.Normalize();

	return Direction * GetMaxVelocity();
}

FVector USteering_SeekBehavior::GetSteering_Implementation() const
{
	ensure(Character);
	
	FVector SteerDirection = GetDesiredVelocity() - GetCurrentVelocity();
	SteerDirection.Normalize();

	return SteerDirection * GetMaxAcceleration();
	
}

FVector USteering_SeekBehavior::GetDestination_Implementation() const
{
	return Target->GetActorLocation();
}
