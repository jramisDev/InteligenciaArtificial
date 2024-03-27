#pragma once

#include "CoreMinimal.h"
#include "SteeringCustom.h"
#include "Steering_SeekBehavior.generated.h"


UCLASS()
class AI2_API USteering_SeekBehavior : public USteeringCustom
{
	GENERATED_BODY()

protected:

	virtual FVector GetDesiredVelocity_Implementation() const override;
	virtual FVector GetSteering_Implementation() const override;
};
