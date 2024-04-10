#include "Steering/SteeringCustom.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USteeringCustom::TicketSteering(float DeltaSeconds)
{
	FVector NewVelocity = GetSteering(DeltaSeconds) * DeltaSeconds + GetCurrentVelocity();

#if WITH_EDITOR
	DrawDebugMovementComponents(DeltaSeconds);
#endif
	
	SetActualVelocity(NewVelocity);

	Character->SetActorRotation(NewVelocity.Rotation());
}

FVector USteeringCustom::GetDesiredVelocity_Implementation(float DeltaSeconds) const
{
	return FVector::ZeroVector;
}

FVector USteeringCustom::GetSteering_Implementation(float DeltaSeconds) const
{
	return FVector::ZeroVector;
}

FVector USteeringCustom::GetDestination_Implementation(float DeltaSeconds) const
{
	return FVector::ZeroVector;
}

void USteeringCustom::SetActualVelocity(const FVector& InVelocity) const
{
	if(UCharacterMovementComponent* Movement = GetMovementComponent())
	{
		Movement->ClearAccumulatedForces();
		Movement->Velocity = InVelocity;
	}
}

UCharacterMovementComponent* USteeringCustom::GetMovementComponent() const
{
	if(Character)
	{
		return Character->FindComponentByClass<UCharacterMovementComponent>();
	}
	return nullptr;
}

FVector USteeringCustom::GetCurrentVelocity() const
{
	if(const UCharacterMovementComponent* Movement = GetMovementComponent())
	{
		return Movement->Velocity;
	}
	return FVector::ZeroVector;
}

float USteeringCustom::GetMaxVelocity() const
{
	if(const UCharacterMovementComponent* Movement = GetMovementComponent())
	{
		return Movement->GetMaxSpeed();
	}
	return INDEX_NONE;
}

float USteeringCustom::GetMaxAcceleration() const
{
	if(const UCharacterMovementComponent* Movement = GetMovementComponent())
	{
		return Movement->GetMaxAcceleration();
	}
	return INDEX_NONE;
}

#if WITH_EDITOR
void USteeringCustom::DrawDebugMovementComponents(float DeltaSeconds)
{
	if(Character)
	{
		//Actual position
		DrawDebugPoint(Character->GetWorld(), Character->GetActorLocation(), 5000.f, FColor::Red, false, 5.f);
		DrawDebugPoint(Character->GetWorld(), GetDestination(DeltaSeconds), 20000.f, FColor::Orange);
		
		//Current velocity
		DrawDebugDirectionalArrow(Character->GetWorld(), Character->GetActorLocation(), Character->GetActorLocation() + GetCurrentVelocity(), 200.f, FColor::Red);
		
		//Steering force
		DrawDebugDirectionalArrow(Character->GetWorld(), Character->GetActorLocation(), Character->GetActorLocation() + GetSteering(DeltaSeconds), 200.f, FColor::Blue);
		
		//Desired velocity
		DrawDebugDirectionalArrow(Character->GetWorld(), Character->GetActorLocation(), Character->GetActorLocation() + GetDesiredVelocity(DeltaSeconds), 200.f, FColor::Green);
	}	
}
#endif
