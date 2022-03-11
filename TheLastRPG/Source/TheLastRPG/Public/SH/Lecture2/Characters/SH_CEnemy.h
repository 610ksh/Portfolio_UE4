#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SH/Lecture2/Components/SH_CStateComponent.h"
#include "SH/Lecture2/SH_ICharacter.h"
#include "SH_CEnemy.generated.h"

UCLASS()
class THELASTRPG_API ASH_CEnemy : public ACharacter, public ISH_ICharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Hitted")
		float LaunchAmount = 100.0f; // ³Ë¹é

protected: // Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

protected: // Actor Component
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USH_CActionComponent* Action;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CStateComponent* State;

public:
	ASH_CEnemy();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void ChangeColor(FLinearColor InColor) override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void RestoreColor();

private:
	void Hitted();
	void Dead();

public:
	virtual void Begin_Dead() override;
	virtual void End_Dead() override;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class AController* DamageInstigator;
	float DamageValue;
};
