#include "Steering/Steering_WanderBehavior.h"

#include "GameFramework/Character.h"

FVector USteering_WanderBehavior::GetDesiredVelocity_Implementation(float DeltaSeconds) const
{
	const FVector WanderVelocity = GetDisplacementVector() + Super::GetDesiredVelocity_Implementation(DeltaSeconds);
	return WanderVelocity;
}

FVector USteering_WanderBehavior::GetDisplacementVector() const
{
	return const_cast<USteering_WanderBehavior*>(this)->GetDisplacementVector();
}

FVector USteering_WanderBehavior::GetDisplacementVector()
{
	FVector CircleCenter = Character->GetActorForwardVector();
	CircleCenter *= WonderFactor;

	FVector DisplacementVector = Character->GetActorForwardVector() * Radius;
	DisplacementVector = DisplacementVector.RotateAngleAxis(WanderAngle, Character->GetActorUpVector());

	WanderAngle += FMath::RandRange(-WanderDeviation, WanderDeviation);

	return DisplacementVector + CircleCenter;
}
