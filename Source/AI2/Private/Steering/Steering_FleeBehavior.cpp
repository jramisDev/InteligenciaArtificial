#include "Steering/Steering_FleeBehavior.h"

FVector USteering_FleeBehavior::GetDesiredVelocity_Implementation(float DeltaSeconds) const
{
	return -Super::GetDesiredVelocity_Implementation(DeltaSeconds);
}
