#include "Release/Actions/CDoAction_Warp.h"
#include "Release/Actions/CAttachment.h"
#include "Release/Global.h"

#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Warp"))
		{
			Decal = Helpers::GetComponent<UDecalComponent>(actor);
			CLog::Log(actor->GetName(), true);
			break;
		}
	}

}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CLog::Log(bEquipped);
}

void ACDoAction_Warp::DoAction()
{

}

void ACDoAction_Warp::Begin_DoAction()
{

}

void ACDoAction_Warp::End_DoAction()
{

}

