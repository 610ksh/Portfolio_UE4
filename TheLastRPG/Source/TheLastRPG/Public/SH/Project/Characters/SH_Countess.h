#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SH_Countess.generated.h"

UCLASS()
class THELASTRPG_API ASH_Countess : public ACharacter
{
	GENERATED_BODY()

public:
	ASH_Countess();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
