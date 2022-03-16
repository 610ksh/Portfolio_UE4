#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_LineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTraceResult, class AActor*, InActor, FLinearColor, InColor);

UCLASS()
class THELASTRPG_API ASH_LineTrace : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:
	ASH_LineTrace();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime);

private:
	UFUNCTION()
		void StartJump(class AActor* InActor, FLinearColor InColor);

protected:
	UFUNCTION(BlueprintCallable)
		void RestoreColor(class ASH_Player* InPlayer);

private:
	TArray<class ASH_Cylinder*> Cylinders;

public:
	UPROPERTY(BlueprintAssignable) // BP에서 이 이벤트를 사용할 수 있게함
		FTraceResult OnTraceResult;
};