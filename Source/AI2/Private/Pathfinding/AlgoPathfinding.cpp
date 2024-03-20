#include "Pathfinding/AlgoPathfinding.h"

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

double UAlgoPathfinding::Heuristic_EuclideanDistance(const UGraphNodeComponent* InOriginNode, const UGraphNodeComponent* InDestNode)
{
	return FVector::Dist(InOriginNode->GetComponentLocation(), InDestNode->GetComponentLocation());
}

void UAlgoPathfinding::AStar(const ANavGraphActor* InNavGraph, TArray<UGraphNodeComponent*>& InPath)
{
	TMap<UGraphNodeComponent*, float> G;
	TMap<UGraphNodeComponent*, float> F;

	TArray<UGraphNodeComponent*> Visitables;
	InNavGraph->GetGraphNodes(Visitables);

	for(const auto Node : Visitables)
	{
		G.Add(Node, UE_MAX_FLT);
		F.Add(Node, UE_MAX_FLT);
	}

	G[InNavGraph->GetStartNode()] = 0.f;
	F[InNavGraph->GetStartNode()] = Heuristic_EuclideanDistance(InNavGraph->GetStartNode(), InNavGraph->GetEndNode());

	TArray<UGraphNodeComponent*> VisitedNodes;
	UGraphNodeComponent* CurrentNode = nullptr;

	//while (!Visitables.IsEmpty())
	while (true)
	{
		CurrentNode = GetShortestNode(Visitables, F);
		Visitables.Remove(CurrentNode);
		VisitedNodes.Add(CurrentNode);
		
		if(CurrentNode == InNavGraph->GetEndNode())
		{
			BackTrack(InNavGraph, F, InPath);
			return;
		}

		for (const auto AdjacentNode : CurrentNode->GetAdjacentNodes())
		{
			const float G_Adjacent = G[CurrentNode] + FVector::Dist(CurrentNode->GetComponentLocation(), AdjacentNode->GetComponentLocation());
			const float H_Adjacent = Heuristic_EuclideanDistance(AdjacentNode, InNavGraph->GetEndNode());
			const float F_Adjacent = G_Adjacent + H_Adjacent;

			if (F[AdjacentNode] > F_Adjacent)
			{
				G[AdjacentNode] = G_Adjacent;
				F[AdjacentNode] = F_Adjacent;
			}
			
		}
	}
	
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
