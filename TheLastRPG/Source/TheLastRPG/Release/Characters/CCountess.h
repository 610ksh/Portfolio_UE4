#pragma once

#include "CoreMinimal.h"
#include "Release/Components/CStateComponent.h"
#include "Release/Characters/ICharacter.h"
#include "GameFramework/Character.h"
#include "CCountess.generated.h"

UCLASS()
class THELASTRPG_API ACCountess : public ACharacter, public IICharacter
{
	GENERATED_BODY()

private: // Scene component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: // Actor component
	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;
	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontageComponent* Montages;

public:
	ACCountess();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	/// Movement
	void OnAvoid();

	void Begin_Roll();
	void Begin_Backstep();

public:
	void End_Roll() override;
	void End_Backstep() override;

private:
	/// Equip
	void OnFist();
	void OnOneHand();
	void OnTwoHand();

	/// Attack
	void OnDoAction();

public:
	virtual void ChangeColor(FLinearColor InColor) override;

private:
	class UMaterialInstanceDynamic* TopMaterial;
	class UMaterialInstanceDynamic* BottomMaterial;

};
