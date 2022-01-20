#include "JG/Actor/JG03_Spawner.h"
#include "JG/JG_Global.h"
#include "JG/Actor/JG02_SpawnActor.h"

AJG03_Spawner::AJG03_Spawner()
{

}

void AJG03_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < 3; i++)
	{
		FTransform transform;
		FVector location = GetActorLocation();

		// (1) ���� ��Ű�鼭 �ٷ� ��ġ ���� (�����ϰ� ��ġ ���� ���Ŀ� �ٸ����� ó���� ��)
		transform.SetLocation(FVector(location.X + i * 400, location.Y, location.Z));
		SpawnActors[i] = GetWorld()->SpawnActor<AJG02_SpawnActor>(SpawnClass[i], transform);

		// (2) ���� ��Ų ���� ��ġ ���� (����� ���ÿ� �ٸ� ������ ó���� ��)
		//SpawnActors[i]->SetActorLocation(FVector(location.X + i * 400, location.Y, location.Z));
	}
}

