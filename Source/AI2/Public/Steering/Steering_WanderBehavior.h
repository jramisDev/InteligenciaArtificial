#pragma once

#include "CoreMinimal.h"
#include "Steering_SeekBehavior.h"
#include "Steering_WanderBehavior.generated.h"


UCLASS()
class AI2_API USteering_WanderBehavior : public USteering_SeekBehavior
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Steering", meta=(AllowPrivateAccess = true))
	float WonderFactor = 100.f;

	UPROPERTY(EditAnywhere, Category = "Steering", meta=(AllowPrivateAccess = true))
	float WanderDeviation = 10.f;
	
	float WanderAngle = 0.f;

	UPROPERTY(EditAnywhere, Category = "Steering", meta=(AllowPrivateAccess = true))
	float Radius = 100.f;
	
protected:

	virtual FVector GetDesiredVelocity_Implementation(float DeltaSeconds) const override;

private:

	FVector GetDisplacementVector() const;
	FVector GetDisplacementVector();
};

