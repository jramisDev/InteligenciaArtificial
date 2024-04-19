﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StateBase.generated.h"

class UFSMComponent;

UENUM()
enum class EFinishStateReason : uint8
{
	None,
	SuccessFinished,
	Abort,
	Interrupted
};

UCLASS(Blueprintable, BlueprintType)
class AI2_API UStateBase : public UObject
{
	GENERATED_BODY()

	friend UFSMComponent;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AActor* StateOwner;

	UFUNCTION(BlueprintNativeEvent)
	void InitState(AActor* InSourceActor);
	
	UFUNCTION(BlueprintNativeEvent)	
	void TickState(float DeltaSeconds);
	
	UFUNCTION(BlueprintNativeEvent)
	void FinishState(EFinishStateReason InFinishedReason);

	UFUNCTION(BlueprintNativeEvent)
	void GetStateDebugInfo(FString& OutInfo);
	
};