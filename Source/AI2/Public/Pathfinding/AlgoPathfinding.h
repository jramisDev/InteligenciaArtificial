#pragma once

#include "CoreMinimal.h"
#include "NavGraphActor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AlgoPathfinding.generated.h"


UCLASS()
class AI2_API UAlgoPathfinding : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void Djikstra(const ANavGraphActor* InNavGraph, TArray<UGraphNodeComponent*>& InPath);

	UFUNCTION(BlueprintCallable)
	static void BackTrack(const ANavGraphActor* InNavGraph, TMap<UGraphNodeComponent*, float> InLowestDistances, TArray<UGraphNodeComponent*>& InPath);

	UFUNCTION(BlueprintCallable)
	static void AStar(const ANavGraphActor* InNavGraph, TArray<UGraphNodeComponent*>& InPath);

private:

	static UGraphNodeComponent* GetShortestNode(TArray<UGraphNodeComponent*> Array, TMap<UGraphNodeComponent*, float> Map);

	static double Heuristic_EuclideanDistance(const UGraphNodeComponent* InOriginNode, const UGraphNodeComponent* InDestNode);
};
