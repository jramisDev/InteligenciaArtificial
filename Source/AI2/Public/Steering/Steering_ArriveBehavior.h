#pragma once

#include "CoreMinimal.h"
#include "Steering_SeekBehavior.h"
#include "Steering_ArriveBehavior.generated.h"

UCLASS()
class AI2_API USteering_ArriveBehavior : public USteering_SeekBehavior
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float DistanceThreshold = 300.f;

	UPROPERTY(EditAnywhere)
	UCurveFloat* Attenuation;

protected:
	virtual FVector GetDesiredVelocity_Implementation(float DeltaSeconds) const override;

	virtual void DrawDebugMovementComponents(float DeltaSeconds) override;
};
