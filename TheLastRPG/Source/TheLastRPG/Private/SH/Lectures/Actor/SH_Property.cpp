#include "SH/Lectures/Actor/SH_Property.h"

// Sets default values
ASH_Property::ASH_Property()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	C = 40;
}

// Called when the game starts or when spawned
void ASH_Property::BeginPlay()
{
	Super::BeginPlay();
	
	//FString str; // F�� ����ü. String�� ���ܷ� F�� ����.
	//str.Append("A : ");
	//str.Append(FString::FromInt(A));
	//str.Append(", ");
	//str.Append("B : ");
	//str.Append(FString::FromInt(B));
	//str.Append(", ");
	//str.Append("C : ");
	//str.Append(FString::FromInt(C));

	// �̱��� GLog (���� ��ü)
	//GLog->Log(str);
}

// Called every frame
void ASH_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

