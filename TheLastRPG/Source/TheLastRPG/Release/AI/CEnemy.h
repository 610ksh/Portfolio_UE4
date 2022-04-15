#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Release/AI/IEnemy.h"
#include "Release/Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class THELASTRPG_API ACEnemy : public ACharacter, public IIEnemy
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Hitted")
		float LaunchAmount = 140.0f;
	UPROPERTY(VisibleAnywhere, Category = "Hitted")
		FLinearColor OriginColor;

protected: // Widget Component
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

protected: // Actor Component
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCActionComponent* Action;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontageComponent* Montages;

public:
	ACEnemy();

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class AController* DamageInstigator; // Other, opponent
	float DamageValue;
};