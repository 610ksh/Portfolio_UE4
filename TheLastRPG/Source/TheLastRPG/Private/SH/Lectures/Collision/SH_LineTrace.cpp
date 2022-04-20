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
		// start -> end �������� ���, "Pawn"�� ã������, �ﰢ������ ���������� �浹��Ű�ųĴ� false
		// ignoreActors : �浹���� ����, ������ ���͵� TArray, 
		// EDrawDebugTrace::ForOneFrame : Debug ��带 ������. �� �����Ӹ��� �׸�����.
		// �浹������ ������ ��� hitResult.
		// �ڱ��ڽ� �浹���� �����ҰųĴ� true�� ����.
		// �浹���� �ʾ����� Į��� Green
		// �浹������ Į��� Red��.
		// �浹 �ð��� Tick���� �ǹ̾����� ������.
		if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true, FLinearColor::Green, FLinearColor::Red))
		{
			if (OnTraceResult.IsBound()) // ����� ��������Ʈ�� �ִٸ�
			{
				FLinearColor color;
				color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.A = 1.0f;

				// �浹�� ���Ϳ� ������ �ѱ��.
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