#include "SH/Lecture2/Components/SH_CFeetComponent.h"
#include "SH/SH_Global.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

USH_CFeetComponent::USH_CFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USH_CFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void USH_CFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance;
	FRotator leftRotation;
	Trace(LeftSocket, leftDistance, leftRotation);

	float rightDistance;
	FRotator rightRotation;
	Trace(RightSocket, rightDistance, rightRotation);

	float offset = FMath::Min(leftDistance, rightDistance); // 더 낮은곳에 있는 발
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);

	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, (leftDistance - offset), DeltaTime, InterpSpeed);
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(rightDistance - offset), DeltaTime, InterpSpeed);

	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);
}

void USH_CFeetComponent::Trace(FName InSocket, float & OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.0f;

	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector start = FVector(location.X, location.Y, OwnerCharacter->GetActorLocation().Z);

	float traceZ = start.Z - OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - TraceDistance; // 땅 아래로 내려감(음수)
	FVector end = FVector(location.X, location.Y, traceZ);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, IgnoreActors, DrawDebugType, hitResult, true, FLinearColor::Green, FLinearColor::Red);

	CheckFalse(hitResult.IsValidBlockingHit()); // 충돌된게 없으면 리턴

	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	// 땅 밑으로 내려가기 때문에 TraceDistance를 마이너스해줘야함.
	OutDistance = -TraceDistance + length + OffsetDistance; // +해주는건 위로 올리는걸 의미함.

	FVector normal = hitResult.ImpactNormal;
	float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(normal.X, normal.Z);

	OutRotation = FRotator(pitch, 0.0f, roll);
}

