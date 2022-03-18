#include "YH/Trace/YH_C2_LineTrace.h"
#include "YH/Global_YH.h"
#include "YH/CPlayer_YH.h"
#include "YH/Trace/YH_C01_Cylinder.h"
#include "Components/TextRenderComponent.h"


AYH_C2_LineTrace::AYH_C2_LineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers_YH::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers_YH::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

}

// Called when the game starts or when spawned
void AYH_C2_LineTrace::BeginPlay()
{
	Super::BeginPlay();

	CHelpers_YH::FindActors<AYH_C01_Cylinder>(GetWorld(), Cylinders);
	OnTraceResult.AddDynamic(this, &AYH_C2_LineTrace::StartJump);
	
}

// Called every frame
void AYH_C2_LineTrace::Tick(float DeltaTime)
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

		//충돌시 제거될애들 
		FHitResult hitResult;//하나라도 충돌되면 true나옴
		if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true, FLinearColor::Green, FLinearColor::Red))
		{
			if (OnTraceResult.IsBound())
			{
				FLinearColor color;
				color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.A = 1.0f;

				OnTraceResult.Broadcast(hitResult.GetActor(), color);
			}
		}//if(LineTraceSingleByProfile)
	}

}

void AYH_C2_LineTrace::StartJump(AActor * InActor, FLinearColor InColor)
{
	ACPlayer_YH* player = Cast<ACPlayer_YH>(InActor);
	YH_CheckNull(player);

	player->Jump();
}

void AYH_C2_LineTrace::RestoreColor(ACPlayer_YH * InPlayer)
{
	InPlayer->ChangeColor(FLinearColor(1, 1, 1));
}
