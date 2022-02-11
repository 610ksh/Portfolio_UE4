#include "SH/Lectures/Debug/SH_Log.h"
#include "SH/SH_Global.h"

// Sets default values
ASH_Log::ASH_Log()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASH_Log::BeginPlay() //
{
	Super::BeginPlay();

	SH_CLog::Print(10);

	SH_CLog::Print(20, 1);
	SH_CLog::Print(30, 2, 20.0f);
	SH_CLog::Print(40, 2, 20.0f);

	SH_CLog::Print("Unreal GamePlay");
	SH_CLog::Print(GetActorLocation());
	SH_CLog::Print(GetActorRotation());

	SH_CLog::Log(55);
	SH_CLog::Log(PI);
	SH_CLog::Log("Unreal GamePlay");
	SH_CLog::Log(GetActorLocation());
	SH_CLog::Log(GetActorRotation());

	SH_CLog::Log(this);
	PrintLine();
}

// Called every frame
void ASH_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	SH_CLog::Print(Time, 3);

}