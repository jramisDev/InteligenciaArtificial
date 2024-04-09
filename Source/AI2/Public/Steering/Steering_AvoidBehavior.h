#pragma once

#include "CoreMinimal.h"
#include "Steering_SeekBehavior.h"
#include "Steering_AvoidBehavior.generated.h"

UCLASS()
class AI2_API USteering_AvoidBehavior : public USteering_SeekBehavior
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Steering", meta = (AllowPrivateAccess = true) )
	float TraceDistance = 300.f;

	UPROPERTY(EditAnywhere, Category = "Steering", meta = (AllowPrivateAccess = true) )
	float UrgentFactor = 1.f;

protected:

	virtual FVector GetDesiredVelocity_Implementation(float DeltaSeconds) const override;

private:

	void DetectObstacleInFront(FHitResult& OutHit) const;
};
