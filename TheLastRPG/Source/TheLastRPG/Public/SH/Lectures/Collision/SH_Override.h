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
	UFUNCTION(BlueprintImplementableEvent) // ������ ������ �̺�Ʈ, �Լ�
		void ChangeColorRed();

	UFUNCTION(BlueprintNativeEvent) // ��ü�� �־����.
		void ChangeColorWhite();

	void ChangeColorWhite_Implementation(); // C++������ _Implementaion�� �����ֱ�. �ٿ��ֱ�. ���ǰ͵� �Ȱ���.

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
