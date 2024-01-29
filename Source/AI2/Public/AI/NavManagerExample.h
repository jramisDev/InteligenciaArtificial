#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavManagerExample.generated.h"

UCLASS()
class AI2_API ANavManagerExample : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANavManagerExample();

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector Goal;

	UPROPERTY(EditAnywhere)
	ACharacter* TargetNavActor;

	UFUNCTION(CallInEditor)
	void SendMoveOrder() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
