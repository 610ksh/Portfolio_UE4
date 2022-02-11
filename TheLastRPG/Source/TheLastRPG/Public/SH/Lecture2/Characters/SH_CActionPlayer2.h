#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SH_CActionPlayer2.generated.h"

UCLASS()
class THELASTRPG_API ASH_CActionPlayer2 : public ACharacter
{
	GENERATED_BODY()

private: // Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: // Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class USH_COptionActorComponent* Option;
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Dodge")
		class UAnimMontage* Montage;

public:
	ASH_CActionPlayer2();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);


private:
	void Dodge();
};
