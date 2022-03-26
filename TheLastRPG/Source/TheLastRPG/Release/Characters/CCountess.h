#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCountess.generated.h"

UCLASS()
class THELASTRPG_API ACCountess : public ACharacter
{
	GENERATED_BODY()

public:
	ACCountess();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
