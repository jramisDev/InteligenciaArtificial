#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UPatrolBehavior : public UObject
{
	GENERATED_BODY()

public:

	virtual AActor* GetNextTargetPatrolPoint(const TArray<AActor*>& PatrolPoints);

private:

	int CurrentPatrolIndex = 0;
};

UCLASS()
class URandomPatrolBehavior : public UPatrolBehavior
{
	GENERATED_BODY()

public:
	virtual AActor* GetNextTargetPatrolPoint(const TArray<AActor*>& PatrolPoints) override;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AI2_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<AActor*> PatrolPoints;

public:

	UPatrolComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UPatrolBehavior> PatrolBehaviorClass;
	
	UFUNCTION(BlueprintCallable)
	virtual AActor* GetNextTargetPatrolPoint();
};
