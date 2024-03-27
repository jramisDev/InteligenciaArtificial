#include "Steering/Steering_SeekBehavior.h"

#include "GameFramework/Character.h"

FVector USteering_SeekBehavior::GetDesiredVelocity_Implementation() const
{
	ensure(Character);
	
	FVector Direction = Destination - Character->GetActorLocation();
	Direction.Normalize();

	return Direction * GetMaxVelocity();
}

FVector USteering_SeekBehavior::GetSteering_Implementation() const
{
	ensure(Character);
	
	FVector SteerDirection = GetDesiredVelocity() - GetCurrentVelocity();
	SteerDirection.Normalize();

	return SteerDirection * GetMaxAcceleration() / Character->GetMesh()->GetMass();
	
}
