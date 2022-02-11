#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_Override.generated.h"

UCLASS()
class THELASTRPG_API ASH_Override : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	ASH_Override();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent) // 재정의 가능한 이벤트, 함수
		void ChangeColorRed();

	UFUNCTION(BlueprintNativeEvent) // 몸체가 있어야함.
		void ChangeColorWhite();

	void ChangeColorWhite_Implementation(); // C++에서는 _Implementaion을 적어주기. 붙여주기. 위의것도 똑같음.

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
