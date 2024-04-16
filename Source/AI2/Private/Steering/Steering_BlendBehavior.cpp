#include "Steering/Steering_BlendBehavior.h"

void USteering_BlendBehavior::Init(ACharacter* InCharacter, AActor* InTarget)
{
	Super::Init(InCharacter, InTarget);
	
	for (const auto& Steering : SteeringData)
	{
		USteeringCustom* SteeringObj = NewObject<USteeringCustom>(this, Steering.SteeringClass);
		ActiveSteeringBehaviors.Add(SteeringObj, Steering.Weight);
		
		SteeringObj->SetAgent(InCharacter);
		SteeringObj->SetTarget(Steering.Target);
	}
	
}

FVector USteering_BlendBehavior::GetSteering_Implementation(float DeltaSeconds) const
{
	FVector TotalSteering;
	
	for (const auto& CurrentSteering : ActiveSteeringBehaviors)
	{
		TotalSteering += (CurrentSteering.Key->GetSteering(DeltaSeconds) * CurrentSteering.Value);
	}

	return Super::GetSteering_Implementation(DeltaSeconds);
}
