#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TransitionBase.generated.h"

class UFSMComponent;

UCLASS(Blueprintable, BlueprintType)
class AI2_API UTransitionBase : public UObject
{
	GENERATED_BODY()

	friend UFSMComponent;

protected:

	UFUNCTION(BlueprintNativeEvent)
	bool CheckCondition(AActor* SourceConditionActor);
	
};
