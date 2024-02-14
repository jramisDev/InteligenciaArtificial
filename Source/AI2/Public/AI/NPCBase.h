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
	
public:
	ANPCBase();

	UPROPERTY(EditInstanceOnly)
	AActor* ReferenceActor;

public:
	virtual void StopMovement_Implementation() override;
	virtual void ResumeMovement_Implementation() override;
};
