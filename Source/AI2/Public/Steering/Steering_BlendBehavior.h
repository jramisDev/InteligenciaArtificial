#pragma once

#include "CoreMinimal.h"
#include "SteeringCustom.h"
#include "Interfaces/ITargetDevice.h"
#include "Steering_BlendBehavior.generated.h"

USTRUCT(BlueprintType)
struct FSteeringData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<USteeringCustom> SteeringClass;
	UPROPERTY(EditAnywhere) float Weight;
	UPROPERTY(EditAnywhere) AActor* Target;
	
};

UCLASS(DefaultToInstanced, EditInlineNew)
class AI2_API USteering_BlendBehavior : public USteeringCustom
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Steering", meta=(AllowPrivateAccess))
	TArray<FSteeringData> SteeringData;

	UPROPERTY(VisibleAnywhere)
	TMap<USteeringCustom*, float> ActiveSteeringBehaviors;

protected:

	virtual void Init(ACharacter* InCharacter, AActor* InTarget) override;
	
	virtual FVector GetSteering_Implementation(float DeltaSeconds) const override;
};
