#include "YH/Debug/YH_C01_Log.h"
#include "YH/Global_YH.h"

AYH_C01_Log::AYH_C01_Log()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AYH_C01_Log::BeginPlay()
{
	Super::BeginPlay();

	YH_CLog::Print(10);

	YH_CLog::Print(20, 1);
	YH_CLog::Print(30, 2, 20.0f);
	YH_CLog::Print(40, 2, 20.0f);

	YH_CLog::Print("Unreal Gameplay!");
	YH_CLog::Print(GetActorLocation());
	YH_CLog::Print(GetActorRotation());

	
	YH_CLog::Log(10);
	YH_CLog::Log(PI);
	YH_CLog::Log("Unreal Gameplay!");
	YH_CLog::Log(GetActorLocation());
	YH_CLog::Log(GetActorRotation());

	YH_CLog::Log(this);
	//CLog::Log(__FUNCTION__, __LINE__);
	YH_PrintLine();
}

void AYH_C01_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	YH_CLog::Print(Time, 3);
}

