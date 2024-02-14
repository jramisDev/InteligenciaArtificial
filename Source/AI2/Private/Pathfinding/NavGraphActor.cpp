#include "Pathfinding/NavGraphActor.h"

#include "Pathfinding/GraphNodeComponent.h"


ANavGraphActor::ANavGraphActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ANavGraphActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (auto GraphNode: GraphNodes)
	{
		if(GraphNode)
		{
			GraphNode->UnregisterComponent();
			GraphNode->MarkAsGarbage();			
		}
	}
	GraphNodes.Reset();

	for (int32 i = 0; i < RowCount; ++i)
	{
		for (int32 j = 0; j < RowCount; ++j)
		{
			const FName NodeName = *FString::Printf(TEXT("Node_%d_%d"), i, j);
			
			UGraphNodeComponent* Node = NewObject<UGraphNodeComponent>(this, NodeName);
			
			Node->SetupAttachment(RootComponent);
			Node->RegisterComponent();			
			Node->SetRelativeLocation({i * DistanceBetweenNodes, j * DistanceBetweenNodes, 0});

			if(Visualizer) Node->SetStaticMesh(Visualizer);

			GraphNodes.Add(Node);
		}
	}

	
}


