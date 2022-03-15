#include "SH/Lectures/Collision/SH_ActorBeginOverlap.h"
#include "SH/SH_Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ASH_ActorBeginOverlap::ASH_ActorBeginOverlap()
{
	SH_CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); // �θ� �ɰŴϱ� �θ� ����.
	SH_CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	SH_CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Box->SetRelativeScale3D(FVector(3)); // Scale �� x,y,z�� 3�� ��.
	Box->bHiddenInGame = false; // ���������� ����ϴ°� �� ����. Set�� �־

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName()); // ��ü�� �̸�, String�� Text�� ��ȯ����.
}

void ASH_ActorBeginOverlap::BeginPlay()
{
	Super::BeginPlay();

	// ���̳��� ��������Ʈ : (�����ü�� �ִ� �Լ��� ȣ������, �Լ��� �ּ�), parameter �ݵ�� ��ġ�ؾ��Ѵ�.
	// Dynamic�� �̸������� ��ġ�ؾ��Ѵ�. �װ� �ƴҶ��� �Ķ���͸� ��ġ�ϸ� ��.
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