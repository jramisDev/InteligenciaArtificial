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

protected:
	virtual FVector GetDesiredVelocity_Implementation() const override;

	virtual void DrawDebugMovementComponents(float DeltaSeconds) override;
};
