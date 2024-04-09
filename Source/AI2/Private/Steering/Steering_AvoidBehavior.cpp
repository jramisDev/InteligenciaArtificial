#include "Steering/Steering_AvoidBehavior.h"

#include "GameFramework/Character.h"

FVector USteering_AvoidBehavior::GetDesiredVelocity_Implementation(float DeltaSeconds) const
{

	FVector CurrentDesiredVelocity = Super::GetDesiredVelocity_Implementation(DeltaSeconds);
	
	FHitResult OutHit;
	DetectObstacleInFront(OutHit);

	if (OutHit.IsValidBlockingHit())
	{
		FVector AvoidanceDir = OutHit.ImpactNormal;
		AvoidanceDir *= UrgentFactor;
		AvoidanceDir *= GetMaxVelocity();

		CurrentDesiredVelocity += AvoidanceDir;

		CurrentDesiredVelocity.Normalize();
		CurrentDesiredVelocity *= GetMaxVelocity();
	}
	
	return CurrentDesiredVelocity;
}

void USteering_AvoidBehavior::DetectObstacleInFront(FHitResult& OutHit) const
{
	
	UWorld* CharacterWorld = Character->GetWorld();

	// TODO Idealmente o static o definidio al nivel de clase
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(TArray<AActor*>{Character, Target});

	CharacterWorld->LineTraceSingleByChannel(
		OutHit,
		Character->GetActorLocation(),
		Character->GetActorLocation() + Character->GetActorForwardVector() * TraceDistance,
		ECC_Visibility,
		QueryParams
		);

	
}
