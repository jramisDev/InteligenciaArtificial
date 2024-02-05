#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_RTS.generated.h"


UCLASS()
class AI2_API AHUD_RTS : public AHUD
{
	GENERATED_BODY()

public:
	
	FVector2D InitialPointSelection;
	FVector2D CurrentPointSelection;

	virtual void DrawHUD() override;
	FVector2D GetMousePos2D();

	bool bStartSelecting = false;
};
