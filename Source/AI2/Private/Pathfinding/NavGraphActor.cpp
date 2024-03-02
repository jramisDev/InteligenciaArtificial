#include "Pathfinding/NavGraphActor.h"

#include "VectorUtil.h"
#include "Pathfinding/AlgoPathfinding.h"
#include "Pathfinding/GraphNodeComponent.h"


ANavGraphActor::ANavGraphActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ANavGraphActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(!bRunConstruction) return;

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

			if(Visualizer) {
				Node->SetStaticMesh(Visualizer);

				if (Cell_SelectedState &&
					SelectedCellIndexes.Contains(FVector2D{static_cast<double>(i),static_cast<double>(j)}))
				{
					Node->SetMaterial(0,Cell_SelectedState);
				}
				if (Cell_Blocked &&
					BlockedCellIndexes.Contains(FVector2D{static_cast<double>(i),static_cast<double>(j)}))
				{
					Node->SetMaterial(0,Cell_Blocked);
					continue;
				}
			}

			GraphNodes.Add(Node);
		}
	}
	
	for (auto Node : GraphNodes)
	{
		TArray<UGraphNodeComponent*> AdjacentNodes = GetAdjacentNodes(Node);
		Node->SetAdjacentNodes(AdjacentNodes);
	}
	
}

void ANavGraphActor::RunPathindingQuery()
{
	ResetNodeStates();
	
	TArray<UGraphNodeComponent*> OutPath;
	UAlgoPathfinding::Djikstra(this, OutPath);
	
	for (auto Node : OutPath)
	{		
		Node->SetMaterial(0,Cell_SelectedState);
	}
}

void ANavGraphActor::ResetNodeStates()
{

	for (auto Node : GraphNodes)
	{
		Node->SetMaterial(0,Cell_DefaultState);
	}
}

void ANavGraphActor::GetBlockNodes()
{

	for(auto Node : GraphNodes)
	{		
		Node->SetMaterial(0, Cell_Blocked);
	}
}

void ANavGraphActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(PropertyChangedEvent.GetMemberPropertyName().IsEqual(GET_MEMBER_NAME_CHECKED(ANavGraphActor, StartNodeCoordinates)))
	{
		StartNodeCoordinates.X = FMath::Clamp(StartNodeCoordinates.X, 0, RowCount-1);		
		StartNodeCoordinates.Y = FMath::Clamp(StartNodeCoordinates.Y, 0, RowCount-1);
		
	}else if(PropertyChangedEvent.GetMemberPropertyName().IsEqual(GET_MEMBER_NAME_CHECKED(ANavGraphActor, EndNodeCoordinates)))
	{
		EndNodeCoordinates.X = FMath::Clamp(EndNodeCoordinates.X, 0, RowCount-1);		
		EndNodeCoordinates.Y = FMath::Clamp(EndNodeCoordinates.Y, 0, RowCount-1);
	}
}

