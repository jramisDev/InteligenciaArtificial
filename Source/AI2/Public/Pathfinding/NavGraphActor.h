#pragma once

#include "CoreMinimal.h"
#include "GraphNodeComponent.h"
#include "IPropertyTable.h"
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

	UPROPERTY(EditAnywhere, Category="Graph")
	UMaterialInterface* Cell_DefaultState;

	UPROPERTY(EditAnywhere, Category="Graph")
	UMaterialInterface* Cell_SelectedState;

	UPROPERTY(EditAnywhere, Category="Graph")
	UMaterialInterface* Cell_Blocked;

	UPROPERTY(EditAnywhere, Category="Graph")
	TArray<FVector2D> SelectedCellIndexes;

	UPROPERTY(EditAnywhere, Category="Graph")
	bool bRunConstruction = false;

	virtual void OnConstruction(const FTransform& Transform) override;

	struct FCoords
	{
		int32 i, j;

		FCoords operator+(const FCoords& Other)
		{
			return {i + Other.i, j + Other.j};
		}
		FCoords operator+(const FCoords& Other) const
		{
			return {i + Other.i, j + Other.j};
		}
	};
	
	inline static const FCoords Up		{-1,0};
	inline static const FCoords Down	{1,0};
	inline static const FCoords Left	{0,-1};
	inline static const FCoords Right	{0,1};
	
	FORCEINLINE uint32 LinealizeCoords(const FCoords& InCoords) const
	{
		return InCoords.i * RowCount + InCoords.j;
	}

	FORCEINLINE void SetAdjacentNodesToNodes(UGraphNodeComponent* Node, const TArray<UGraphNodeComponent*>& InAdjacentNodes) const
	{
		Node->SetAdjacentNodes(InAdjacentNodes);
	}

	FORCEINLINE FCoords CoordinatesFromLinearIndex(const SIZE_T Index) const
	{
		return FCoords{static_cast<int32>(Index / RowCount),static_cast<int32>(Index % RowCount)};
	}

	FORCEINLINE TArray<UGraphNodeComponent*> GetAdjacentNodes(UGraphNodeComponent* Node) const
	{

		TArray<UGraphNodeComponent*> OutNodes;
		
		const SIZE_T Index = GraphNodes.Find(Node);
		const FCoords NodeCoord = CoordinatesFromLinearIndex(Index);
		
		const FCoords Node_Up		= ANavGraphActor::Up		+ NodeCoord;
		const FCoords Node_Down		= ANavGraphActor::Down		+ NodeCoord;
		const FCoords Node_Left		= ANavGraphActor::Left		+ NodeCoord;
		const FCoords Node_Right	= ANavGraphActor::Right		+ NodeCoord;

		if (GraphNodes.IsValidIndex(LinealizeCoords(Node_Up)))		OutNodes.Add(GraphNodes[LinealizeCoords(Node_Up)]);
		if (GraphNodes.IsValidIndex(LinealizeCoords(Node_Down)))	OutNodes.Add(GraphNodes[LinealizeCoords(Node_Down)]);
		if (GraphNodes.IsValidIndex(LinealizeCoords(Node_Left)))	OutNodes.Add(GraphNodes[LinealizeCoords(Node_Left)]);
		if (GraphNodes.IsValidIndex(LinealizeCoords(Node_Right)))	OutNodes.Add(GraphNodes[LinealizeCoords(Node_Right)]);

		for(auto OutNode : OutNodes)
		{
			UE_LOG(LogTemp, Display, TEXT("CurrentNode: %s, AdjacentNode: %s"), *Node->GetName(), *OutNode->GetName())			
		}

		return OutNodes;
	}
};
