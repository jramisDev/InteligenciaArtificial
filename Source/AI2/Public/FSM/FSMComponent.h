#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FSMComponent.generated.h"


class UStateBase;
class UFSMBaseAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AI2_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStateBase* ActiveState;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UFSMBaseAsset* ActiveFSM;
	

protected:
	UFSMComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetNewState(TSubclassOf<UStateBase> InNextSate);

#if WITH_EDITOR
	virtual void ShowDebugStateMachine(float DeltaTime) const;
#endif

public:

	UFUNCTION(BlueprintCallable)
	void SetNextSate(TSubclassOf<UStateBase> InNextSate);

private:

	bool IsStateAvailable(TSubclassOf<UStateBase> InQueriedState);
	
};
