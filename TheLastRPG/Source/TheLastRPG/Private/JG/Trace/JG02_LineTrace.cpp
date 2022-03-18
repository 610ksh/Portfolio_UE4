// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/Trace/JG02_LineTrace.h"
#include "JG/Trace/JG01_Cylinder.h"
#include "JG/JG_Player.h"
#include "JG/JG_Global.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AJG02_LineTrace::AJG02_LineTrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	JG_Helpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());
}

// Called when the game starts or when spawned
void AJG02_LineTrace::BeginPlay()
{
	Super::BeginPlay();

	JG_Helpers::FindActors<AJG01_Cylinder>(GetWorld(), Cylinders);

	JG_OnTraceResult.AddDynamic(this, &AJG02_LineTrace::StartJump);
}

// Called every frame
void AJG02_LineTrace::Tick(float DeltaTime)
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
		if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true, FLinearColor::Green, FLinearColor::Red))
		{
			if (JG_OnTraceResult.IsBound()) 
			{
				FLinearColor color;
				color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.A = 1.0f;

				JG_OnTraceResult.Broadcast(hitResult.GetActor(), color);
				JG_Log::Log(hitResult.GetActor()->GetName());
			}
		}//if(LineTraceSingleByProfile()) // 중괄호 구분점
	}
}

void AJG02_LineTrace::StartJump(AActor* InActor, FLinearColor InColor)
{
	AJG_Player* player = Cast<AJG_Player>(InActor);
	JG_CheckNull(player);

	player->Jump();
}

void AJG02_LineTrace::RestoreColor(AJG_Player* InPlayer)
{
	InPlayer->ChangeColor(FLinearColor(1, 1, 1));
}