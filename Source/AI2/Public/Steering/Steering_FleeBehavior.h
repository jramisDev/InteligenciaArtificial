#pragma once

#include "CoreMinimal.h"
#include "Steering_SeekBehavior.h"
#include "Steering_FleeBehavior.generated.h"

UCLASS()
class AI2_API USteering_FleeBehavior : public USteering_SeekBehavior
{
	GENERATED_BODY()

protected:
	virtual FVector GetDesiredVelocity_Implementation(float DeltaSeconds) const override;
};
