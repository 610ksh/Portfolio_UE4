#include "SH/Lectures/Collision/SH_LineTrace.h"
#include "SH/Lectures/Collision/SH_Cylinder.h"
#include "SH/Lectures/SH_Player.h"
#include "SH/SH_Global.h"
#include "Components/TextRenderComponent.h"

ASH_LineTrace::ASH_LineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());
}

void ASH_LineTrace::BeginPlay()
{
	Super::BeginPlay();

	SH_CHelpers::FindActors<ASH_Cylinder>(GetWorld(), Cylinders);

	OnTraceResult.AddDynamic(this, &ASH_LineTrace::StartJump);
}

void ASH_LineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();

	//DrawDebugLine
	{
		start.Z -= 10;
		end.Z -= 10;

		DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false);
	}

	//Line Trace
	{
		start.Z += 10;
		end.Z += 10;

		TArray<AActor*> ignoreActors;
		ignoreActors.Add(Cylinders[0]);
		ignoreActors.Add(Cylinders[1]);

		FHitResult hitResult;
		// start -> end 방향으로 쏘고, "Pawn"을 찾을거임, 삼각형마다 복합적으로 충돌시키거냐는 false
		// ignoreActors : 충돌에서 예외, 제거할 액터들 TArray, 
		// EDrawDebugTrace::ForOneFrame : Debug 모드를 지정함. 매 프레임마다 그릴거임.
		// 충돌했을때 정보를 담는 hitResult.
		// 자기자신 충돌에서 제외할거냐는 true로 해줌.
		// 충돌하지 않았을때 칼라는 Green
		// 충돌했을때 칼라는 Red로.
		// 충돌 시간은 Tick에서 의미없으니 무시함.
		if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true, FLinearColor::Green, FLinearColor::Red))
		{
			if (OnTraceResult.IsBound()) // 연결된 델리게이트가 있다면
			{
				FLinearColor color;
				color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.A = 1.0f;

				// 충돌된 액터와 색깔을 넘긴다.
				OnTraceResult.Broadcast(hitResult.GetActor(), color);
				SH_CLog::Log(hitResult.GetActor()->GetName());
			}
		}//if(LineTraceSingleByProfile())
	}
}

void ASH_LineTrace::StartJump(AActor* InActor, FLinearColor InColor)
{
	ASH_Player* player = Cast<ASH_Player>(InActor);
	SH_CheckNull(player);

	player->Jump();
}

void ASH_LineTrace::RestoreColor(ASH_Player* InPlayer)
{
	InPlayer->ChangeColor(FLinearColor(1, 1, 1));
}