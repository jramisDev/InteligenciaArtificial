#include "Steering/Steering_BlendBehavior.h"

FVector USteering_BlendBehavior::GetSteering_Implementation(float DeltaSeconds) const
{
	FVector TotalSteering;
	
	for (const auto Steering : BlendBehaviorWeights)
	{
		TotalSteering += Steering.Key->GetSteering(DeltaSeconds) * Steering.Value;
	}

	return Super::GetSteering_Implementation(DeltaSeconds);
}
