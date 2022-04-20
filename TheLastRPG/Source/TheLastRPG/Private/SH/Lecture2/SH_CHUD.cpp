#include "SH/Lecture2/SH_CHUD.h"
#include "SH/SH_Global.h"

#include "Engine/Texture2D.h"
#include "Engine/Canvas.h"

ASH_CHUD::ASH_CHUD()
{
	SH_CHelpers::GetAsset<UTexture2D>(&Texture, "Texture2D'/Game/Lectures/Textures/T_Crosshair.T_Crosshair'");
}

void ASH_CHUD::DrawHUD()
{
	Super::DrawHUD();

	SH_CheckFalse(bDraw);
	SH_CheckNull(Texture);

	FVector2D center(Canvas->ClipX*0.5f, Canvas->ClipY*0.5f);
	FVector2D size(Texture->GetSurfaceWidth()*0.5f, Texture->GetSurfaceHeight()*0.5f);
	FVector2D position = center - size;

	FCanvasTileItem item(position, Texture->Resource, FLinearColor::White);
	item.BlendMode = SE_BLEND_Translucent;

	Canvas->DrawItem(item);
}