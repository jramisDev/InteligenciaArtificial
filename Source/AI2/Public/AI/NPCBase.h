﻿#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class AI2_API ANPCBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	ANPCBase();

	UPROPERTY(EditInstanceOnly)
	AActor* ReferenceActor;

protected:
	virtual void BeginPlay() override;

	AAIControllerBase* AIControllerBase;
};
