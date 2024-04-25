#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Net/Core/PushModel/PushModel.h"
#include "FSMBaseAsset.generated.h"

class UTransitionBase;
class UStateBase;

USTRUCT()
struct FTransitionCollection
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UTransitionBase>> Transitions;
	
};

USTRUCT(BlueprintType)
struct FStateConditionEvalExpr
{
	GENERATED_BODY()	

	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<UStateBase>, FTransitionCollection> AvailableStates;
};

UCLASS()
class AI2_API UFSMBaseAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStateBase> InitialState;
	
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<UStateBase>, FStateConditionEvalExpr> FSM;
};
