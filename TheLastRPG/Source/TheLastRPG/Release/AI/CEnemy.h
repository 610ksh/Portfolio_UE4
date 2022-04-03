#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Release/AI/IEnemy.h"
#include "CEnemy.generated.h"

UCLASS()
class THELASTRPG_API ACEnemy : public ACharacter, public IIEnemy
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ChangeColor(FLinearColor InColor) override;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;
};