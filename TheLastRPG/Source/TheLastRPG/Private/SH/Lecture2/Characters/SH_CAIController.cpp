#include "SH/Lecture2/Characters/SH_CAIController.h"
#include "SH/Lecture2/Characters/SH_CActionPlayer.h"
#include "SH/Lecture2/Characters/SH_CEnemy_AI.h"
#include "SH/Lecture2/Components/SH_CBehaviorComponent.h"
#include "SH/SH_Global.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ASH_CAIController::ASH_CAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	SH_CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");
	SH_CHelpers::CreateActorComponent<USH_CBehaviorComponent>(this, &Behavior, "Behavior");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 600; // �þ߹���
	Sight->LoseSightRadius = 800; // �Ҿ����� ����
	Sight->PeripheralVisionAngleDegrees = 90; // �þ߰�
	Sight->SetMaxAge(2); // �Ҿ����� �󸶸�ŭ ������

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

float ASH_CAIController::GetSightRadius()
{
	return Sight->SightRadius;
}

void ASH_CAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bDrawDebug);

	FVector center = OwnerEnemy->GetActorLocation();
	center.Z -= AdjustCircleHeight;
	DrawDebugCircle(GetWorld(), center, Sight->SightRadius, 300, FColor::Green, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector);
	DrawDebugCircle(GetWorld(), center, MeleeActionRange, 300, FColor::Red, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector);
}

void ASH_CAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	OwnerEnemy = Cast<ASH_CEnemy_AI>(InPawn);
	SetGenericTeamId(OwnerEnemy->GetTeamID());

	Perception->OnPerceptionUpdated.AddDynamic(this, &ASH_CAIController::OnPerceptionUpdated);

	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
}

void ASH_CAIController::OnUnPossess()
{
	Super::OnUnPossess();
	Perception->OnPerceptionUpdated.Clear();
}

void ASH_CAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(NULL, actors);

	ASH_CActionPlayer* player = NULL;
	for (AActor* actor : actors)
	{
		player = Cast<ASH_CActionPlayer>(actor);
		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject("Player", player);
}
