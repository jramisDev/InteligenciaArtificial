#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GraphNodeComponent.generated.h"

UCLASS()
class AI2_API UGraphNodeComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere)
	TArray<UGraphNodeComponent*> AdjacentNodes;

public:

	void SetAdjacentNodes(const TArray<UGraphNodeComponent*>& InAdjacentNodes){ AdjacentNodes = InAdjacentNodes; };
};
