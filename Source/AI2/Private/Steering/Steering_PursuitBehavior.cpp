#include "Steering/Steering_PursuitBehavior.h"

FVector USteering_PursuitBehavior::GetDestination_Implementation(float DeltaSeconds) const
{
	return Target->GetActorLocation() + Target->GetVelocity() * PredictionDeltaTime;
}

#if WITH_EDITOR
void USteering_PursuitBehavior::DrawDebugMovementComponents(float DeltaSeconds)
{
	Super::DrawDebugMovementComponents(DeltaSeconds);

	DrawDebugPoint(GetWorld(), GetDestination(DeltaSeconds), 1000.f, FColor::Black, false, 5.f);
}
#endif