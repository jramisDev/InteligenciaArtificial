#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavGraphActor.generated.h"

class UGraphNodeComponent;

UCLASS()
class AI2_API ANavGraphActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="Graph")
	TArray<UGraphNodeComponent*> GraphNodes;

public:
	ANavGraphActor();

	UPROPERTY(EditAnywhere, Category="Graph")
	int32 RowCount = 4;

	UPROPERTY(EditAnywhere, Category="Graph")
	float DistanceBetweenNodes = 100.f;

	UPROPERTY(EditAnywhere, Category="Graph")
	UStaticMesh* Visualizer;

	virtual void OnConstruction(const FTransform& Transform) override;
};
