#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class AI2_API ANPCBase : public ACharacter, public IAIMovementInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "AIData", meta=(AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTreeAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "AIData", meta=(AllowPrivateAccess = true))
	UBlackboardData* BlackboardData;
	
public:
	
	ANPCBase();

	UPROPERTY(EditInstanceOnly)
	AActor* ReferenceActor;

	UPROPERTY(EditAnywhere, Category = "AIData", meta=(AllowPrivateAccess = true))
	AActor* PatrolPointOrigin;
	
	UPROPERTY(EditAnywhere, Category = "AIData", meta=(AllowPrivateAccess = true))
	AActor* PatrolPointDestiny;

	UPROPERTY(EditAnywhere, Category = "AIData", meta=(AllowPrivateAccess = true))
	TArray<AActor*> ArrayPatrolPoints;

	UBehaviorTree* GetDefaultBehavior() const { return BehaviorTreeAsset; }
	UBlackboardData* GetDefaultBlackboard() const { return BlackboardData; }
	
public:
	virtual void StopMovement_Implementation() override;
	virtual void ResumeMovement_Implementation() override;
};
