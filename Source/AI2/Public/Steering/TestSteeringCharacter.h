﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestSteeringCharacter.generated.h"

class USteeringCustom;

UCLASS()
class AI2_API ATestSteeringCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Instanced, meta=(ShowOnlyInnerProperties=true))
	USteeringCustom* CurrentSteeringBehavior;

	UPROPERTY(EditAnywhere, Category = "Steering Behaviors", meta=(AllowPrivateAccess=true))
	TSubclassOf<USteeringCustom> InitialSteeringClass;

	UPROPERTY(EditAnywhere, Category = "Steering Behaviors", meta=(AllowPrivateAccess=true))
	AActor* TargetActor;
	
public:
	ATestSteeringCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};