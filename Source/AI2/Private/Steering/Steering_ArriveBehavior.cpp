#include "Steering/Steering_ArriveBehavior.h"

#include "GameFramework/Character.h"

FVector USteering_ArriveBehavior::GetDesiredVelocity_Implementation(float DeltaSeconds) const
{
	FVector CurrentDesiredVelocity = Super::GetDesiredVelocity_Implementation(DeltaSeconds); 

	const float Distance = FVector::Distance(Character->GetActorLocation(), GetDestination(DeltaSeconds)); 
	if(Distance < DistanceThreshold)
	{
		float AttenuationCoeff = 1.f;
		if(Attenuation)
		{
			AttenuationCoeff = Attenuation->GetFloatValue(Distance / DistanceThreshold);
		}
		else
		{
			AttenuationCoeff = Distance / DistanceThreshold;
		}
		
		CurrentDesiredVelocity *= AttenuationCoeff; 
	}
	
	return CurrentDesiredVelocity;
}

void USteering_ArriveBehavior::DrawDebugMovementComponents(float DeltaSeconds)
{
	Super::DrawDebugMovementComponents(DeltaSeconds);

	//DrawDebugCircle(Character->GetWorld(), Destination, DistanceThreshold, 10.f, FColor::Green, false, DeltaSeconds, 0, 100.f, FVector::ForwardVector, FVector::UpVector);
}
