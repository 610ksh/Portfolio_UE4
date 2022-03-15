#include "SH/Lectures/Debug/SH_Log.h"
#include "SH/SH_Global.h"

/*
	Test를 위한 Log클래스임.
	CLog 클래스에 있는 Log기능을 활용함.
*/

ASH_Log::ASH_Log()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASH_Log::BeginPlay()
{
	Super::BeginPlay();

	SH_CLog::Print(10);

	SH_CLog::Print(20, 1);
	SH_CLog::Print(30, 2, 20.0f);
	SH_CLog::Print(40, 2, 10.0f);

	SH_CLog::Print("Unreal GamePlay");
	SH_CLog::Print(GetActorLocation());
	SH_CLog::Print(GetActorRotation());

	SH_CLog::Log(55);
	SH_CLog::Log(PI);
	SH_CLog::Log("Unreal GamePlay");
	SH_CLog::Log(GetActorLocation());
	SH_CLog::Log(GetActorRotation());

	SH_CLog::Log(this);
	//SH_CLog::Log(__FUNCTION__, __LINE__); // PrintLine_SH와 동일함
	PrintLine_SH();
}

void ASH_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	SH_CLog::Print(Time, 3); // 3번째 위치에 출력.

}