#include "Steering/SteeringCustom.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USteeringCustom::TicketSteering(float DeltaSeconds)
{
	FVector NewVelocity = GetSteering() * DeltaSeconds + GetCurrentVelocity();

	SetActualVelocity(NewVelocity * DeltaSeconds);
}

FVector USteeringCustom::GetDesiredVelocity_Implementation() const
{
	return FVector::ZeroVector;
}

FVector USteeringCustom::GetSteering_Implementation() const
{
	return FVector::ZeroVector;
}

void USteeringCustom::SetActualVelocity(const FVector& InVelocity) const
{
	if(UCharacterMovementComponent* Movement = GetMovementComponent())
	{
		Movement->Velocity = InVelocity;

		Movement->AddInputVector(InVelocity);
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
		//Steering acceleration
		//DrawDirectionalArrow(Character->GetWorld(), Character->GetActorLocation(), GetSteering() - Character->GetActorLocation(), 5.f, FColor::Red);
		//Desired velocity
		//DrawDirectionalArrow();
		//Current velocity
		//DrawDirectionalArrow();
	}	
}
#endif
