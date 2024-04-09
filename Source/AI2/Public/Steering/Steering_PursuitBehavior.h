#pragma once

#include "CoreMinimal.h"
#include "Steering_SeekBehavior.h"
#include "Steering_PursuitBehavior.generated.h"

UCLASS()
class AI2_API USteering_PursuitBehavior : public USteering_SeekBehavior
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Steering", meta = (AllowPrivateAccess = true) )
	float PredictionDeltaTime = 0.5f;

protected:
	
	virtual FVector GetDestination_Implementation(float DeltaSeconds) const override;

	virtual void DrawDebugMovementComponents(float DeltaSeconds) override;
};
