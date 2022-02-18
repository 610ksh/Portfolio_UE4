#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SH_CHUD.generated.h"

UCLASS()
class THELASTRPG_API ASH_CHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;

public:
	FORCEINLINE void SetDrawMode() { bDraw = true; }
	FORCEINLINE void SetUndrawMode() { bDraw = false; }

public:
	ASH_CHUD();

	virtual void DrawHUD() override;

private:
	bool bDraw;
};
