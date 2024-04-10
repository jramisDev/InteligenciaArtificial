#pragma once

#include "CoreMinimal.h"
#include "SteeringCustom.h"
#include "Steering_BlendBehavior.generated.h"

UCLASS()
class AI2_API USteering_BlendBehavior : public USteeringCustom
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Steering")
	TMap<USteeringCustom*, float> BlendBehaviorWeights;

protected:
	virtual FVector GetSteering_Implementation(float DeltaSeconds) const override;
};
