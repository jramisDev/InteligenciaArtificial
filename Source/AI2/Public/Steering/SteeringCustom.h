#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SteeringCustom.generated.h"

class UCharacterMovementComponent;

UCLASS()
class AI2_API USteeringCustom : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Transient)
	ACharacter* Character;

	UPROPERTY(Transient)
	FVector Destination;

public:

	void TicketSteering(float DeltaSeconds);
	
	void SetAgent(ACharacter* InAgent) {Character = InAgent; }
	void SetDestination(const FVector& InDestination) {Destination = InDestination; }

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "SteeringBehaviors")
	FVector GetDesiredVelocity() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "SteeringBehaviors")
	FVector GetSteering() const;

	void SetActualVelocity(const FVector& InVelocity) const;

	FORCEINLINE UCharacterMovementComponent* GetMovementComponent() const;
	FORCEINLINE FVector GetCurrentVelocity() const;
	FORCEINLINE float GetMaxVelocity() const;
	FORCEINLINE float GetMaxAcceleration() const;

#if WITH_EDITOR
	void DrawDebugMovementComponents(float DeltaSeconds);
#endif
	

};
