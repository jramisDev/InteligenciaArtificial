#include "UI/HUD_RTS.h"

#include "AI/NPCBase.h"
#include "Core/AI2PlayerController.h"

void AHUD_RTS::DrawHUD()
{
	Super::DrawHUD();

	//if(bStartSelecting){
		CurrentPointSelection = GetMousePos2D();
		DrawRect(FLinearColor(0,0,1,.15f),
			InitialPointSelection.X, InitialPointSelection.Y,
			CurrentPointSelection.X - InitialPointSelection.X,
			CurrentPointSelection.Y - InitialPointSelection.Y);
		
		// TArray<ANPCBase*> ActorsInSelectionRect;
		// if(!GetActorsInSelectionRectangle<ANPCBase>(InitialPointSelection, CurrentPointSelection, ActorsInSelectionRect)) return;
		//
		// if(AAI2PlayerController* AIController = Cast<AAI2PlayerController>(GetOwningPlayerController()))
		// {
		// 	AIController->NPCArray = ActorsInSelectionRect;
		// }
	//}
}

FVector2D AHUD_RTS::GetMousePos2D()
{
	float PositionX;
	float PositionY;
	
	GetOwningPlayerController()->GetMousePosition(PositionX, PositionY);
	
	return FVector2D(PositionX, PositionY);
}
