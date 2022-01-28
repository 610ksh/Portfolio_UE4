// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JG_Rifle.generated.h"

UCLASS()
class THELASTRPG_API AJG_Rifle : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
	FName HandSocket = "Hand_Rifle";

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
	FName HolsterSocket = "Holster_Rifle";

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
	class UAnimMontage* GrabMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
	class UAnimMontage* UngrabMontage;

public:
	// ���丮 ���� : ����� ������ų�� ���������� ó���ؼ� ���Ͻ����ִ� ���
	// �������� �κи� ������ �� �ֱ� ������ �ܺο��� ó���ϴ°ͺ��� ����
	static AJG_Rifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	// � �÷����̵�(�����̵� �ý��� ������� ��������) �ζ��� �Լ� ����϶�
	// �ζ����� �Լ��� ȣ���ϴ� �ڵ带 �Լ��� ���ǵ� ������ �������� �ʰ� �����Ϸ��� ������ �Լ�ü�� �Լ��� ȣ��Ǵ� ��� ��ҿ� ������ ���� ��û�ϴ� �Լ�
	// ��, �Ϲ��Լ��� ȣ���ϸ� �ش� �Լ��� �ּҷ� ���ٰ� ����ϰ� ���ƿ��� ������ ���ľ��ϴµ� inline �Լ��� �̹� ġȯ�Ǿ������Ƿ� ���� �Լ� ȣ�� ������ ���ؼ� �ּҸ� �̵��� �ʿ���� �� ��ġ���� ó���ϹǷ� �ӵ��� ����.
	// �𸮾��� �ζ��� �Լ��� ����� ���� ������
	FORCEINLINE bool GetEquipped() { return bEquipped; }
	FORCEINLINE bool GetEquipping() { return bEquipping; }

public:	
	// Sets default values for this actor's properties
	AJG_Rifle();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
};
