#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SH_CAIController.generated.h"

UCLASS()
class THELASTRPG_API ASH_CAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.0f; // ���ݹ���
	UPROPERTY(EditAnywhere)
		bool bDrawDebug = true; // ����� ���
	UPROPERTY(EditAnywhere)
		float AdjustCircleHeight = 50.0f; // 

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception; // ���� ����
	UPROPERTY(VisibleDefaultsOnly)
		class USH_CBehaviorComponent* Behavior;

public:
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

public:
	ASH_CAIController();

	float GetSightRadius();
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);

private:
	class ASH_CEnemy_AI* OwnerEnemy;
	class UAISenseConfig_Sight* Sight; // �þ� ����
};
