#include "SH/Lectures/Collision/SH_ActorBeginOverlap.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ASH_ActorBeginOverlap::ASH_ActorBeginOverlap()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); // 부모가 될거니까 부모를 비어둠.
	SH_CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Box->SetRelativeScale3D(FVector(3)); // x,y,z에 3배씩 들어감
	Box->bHiddenInGame = false; // 지역변수를 사용하는게 더 좋음. Set이 있어도

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName()); // 객체의 이름, String을 Text로 변환해줌.
}

void ASH_ActorBeginOverlap::BeginPlay()
{
	Super::BeginPlay();

	//다이나믹 델리게이트 : (어느객체에 있는 함수를 호출할지, 함수의 주소), parameter 반드시 일치해야한다.
	// Dynamic은 이름까지도 일치해야한다. 그게 아닐때는 파라미터만 일치하면 됨.
	OnActorBeginOverlap.AddDynamic(this, &ASH_ActorBeginOverlap::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ASH_ActorBeginOverlap::ActorEndOverlap);
}

void ASH_ActorBeginOverlap::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	FString str = "";
	str.Append("C++ Actor Begin Overlap : ");
	str.Append(OtherActor->GetName());

	SH_CLog::Log(str);
}

void ASH_ActorBeginOverlap::ActorEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	FString str = "";
	str.Append("C++ Actor End Overlap : ");
	str.Append(OtherActor->GetName());

	SH_CLog::Log(str);
}