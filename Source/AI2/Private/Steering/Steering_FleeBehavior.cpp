#include "Steering/Steering_FleeBehavior.h"

FVector USteering_FleeBehavior::GetDesiredVelocity_Implementation() const
{
	return -Super::GetDesiredVelocity_Implementation();
}
