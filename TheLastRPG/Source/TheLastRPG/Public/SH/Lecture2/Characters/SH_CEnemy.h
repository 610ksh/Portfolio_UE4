#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SH/Lecture2/SH_ICharacter.h"
#include "SH_CEnemy.generated.h"

UCLASS()
class THELASTRPG_API ASH_CEnemy : public ACharacter, public ISH_ICharacter
{
	GENERATED_BODY()

public:
	ASH_CEnemy();

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
