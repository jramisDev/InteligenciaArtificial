#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GraphNodeComponent.generated.h"

UENUM()
enum ENodeStatus
{
	Base,
	Blocked,
	Pathing
};

UCLASS()
class AI2_API UGraphNodeComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere)
	TArray<UGraphNodeComponent*> AdjacentNodes;

	ENodeStatus StatusNode = ENodeStatus::Base;

public:

	void SetAdjacentNodes(const TArray<UGraphNodeComponent*>& InAdjacentNodes){ AdjacentNodes = InAdjacentNodes; };

	const TArray<UGraphNodeComponent*>& GetAdjacentNodes() const { return AdjacentNodes; }

	void SetStatusNode(const ENodeStatus InStatusNode)
	{
		StatusNode = InStatusNode;

		InStatusNode
	}

};
