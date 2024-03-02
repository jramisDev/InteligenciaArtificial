#include "Pathfinding/AlgoPathfinding.h"

#include "AITypes.h"

void UAlgoPathfinding::Djikstra(const ANavGraphActor* InNavGraph, TArray<UGraphNodeComponent*>& Path)
{

	//Configuración del algoritmo
	TMap<UGraphNodeComponent*, float> LowestDistanceFromStartNode;

	TArray<UGraphNodeComponent*> PendingNodes;
	InNavGraph->GetGraphNodes(PendingNodes);

	for(auto Node : PendingNodes)
	{		
		if(Node == InNavGraph->GetStartNode())
		{
			LowestDistanceFromStartNode.Add(Node, 0);
		}else
		{
			LowestDistanceFromStartNode.Add(Node, 1E8);
		}
	}

	// Bucle del algoritmo
	while(!PendingNodes.IsEmpty())
	{
		UGraphNodeComponent* ShortestDistanceNode = GetShortestNode(PendingNodes, LowestDistanceFromStartNode);
		PendingNodes.Remove(ShortestDistanceNode);

		for(auto AdjacenteNode : ShortestDistanceNode->GetAdjacentNodes())
		{
			const float DistanceToNode =
				FVector::Distance(ShortestDistanceNode->GetRelativeLocation(), AdjacenteNode->GetRelativeLocation())
				+ LowestDistanceFromStartNode[ShortestDistanceNode];

			if (LowestDistanceFromStartNode[AdjacenteNode] > DistanceToNode)
			{
				LowestDistanceFromStartNode[AdjacenteNode] = DistanceToNode;
			}
		}
	}

	UAlgoPathfinding::BackTrack(InNavGraph, LowestDistanceFromStartNode, Path);
}	

void UAlgoPathfinding::BackTrack(const ANavGraphActor* InNavGraph, TMap<UGraphNodeComponent*, float> InLowestDistances, TArray<UGraphNodeComponent*>& Path)
{
	UGraphNodeComponent* CurrentBestNode = InNavGraph->GetEndNode();
	
	while (CurrentBestNode != InNavGraph->GetStartNode())
	{
		Path.Add(CurrentBestNode);
		CurrentBestNode = GetShortestNode(CurrentBestNode->GetAdjacentNodes(), InLowestDistances);
	}

	Path.Add(CurrentBestNode);
}

UGraphNodeComponent* UAlgoPathfinding::GetShortestNode(TArray<UGraphNodeComponent*> PendingNodes, TMap<UGraphNodeComponent*, float> LowestDistanceMap)
{
	float BestDistance = 1E8;
	UGraphNodeComponent* BestNode = nullptr;

	for (auto Node : PendingNodes)
	{
		if(LowestDistanceMap[Node] < BestDistance)
		{
			BestDistance = LowestDistanceMap[Node];
			BestNode = Node;
		}
	}
	return BestNode;
}
