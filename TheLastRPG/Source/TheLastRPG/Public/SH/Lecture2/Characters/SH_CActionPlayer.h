#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/SH_ICharacter.h"
#include "SH_CActionPlayer.generated.h"

UCLASS()
class THELASTRPG_API ASH_CActionPlayer : public ACharacter, public ISH_ICharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class USH_CUserWidget_ActionList> ActionListClass;

private: // Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: // Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CActionComponent* Action;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CTargetComponent* Target;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_COptionActorComponent* Option;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CStateComponent* State;

public:
	FORCEINLINE class USH_CUserWidget_ActionList* GetActionList() { return ActionList; }

public:
	ASH_CActionPlayer();

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
	void OnAvoid();

private:
	UFUNCTION() // for Delegate about StateComponent
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void Begin_Roll();
	void Begin_Backstep();

public:
	void End_Roll();
	void End_Backstep();

private:
	UFUNCTION()
		void OnFist();
	UFUNCTION()
		void OnOneHand();
	UFUNCTION()
		void OnTwoHand();
	UFUNCTION()
		void OnWarp();
	UFUNCTION()
		void OnFireStorm();
	UFUNCTION()
		void OnIceBall();

	void OnDoAction();

	void OnTarget();
	void OnTargetLeft();
	void OnTargetRight();

	void OnAim();
	void OffAim();

	void OnViewActionList();
	void OffViewActionList();

public:
	virtual void ChangeColor(FLinearColor InColor) override;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class USH_CUserWidget_ActionList* ActionList;
};
