#include "SH/Lecture2/Components/SH_CPatrolComponent.h"
#include "SH/Lecture2/Actors/SH_CPatrolPath.h"
#include "SH/SH_Global.h"

#include "Components/SplineComponent.h"

USH_CPatrolComponent::USH_CPatrolComponent()
{

}

void USH_CPatrolComponent::BeginPlay()
{
	Super::BeginPlay();
}


bool USH_CPatrolComponent::GetMoveTo(FVector & OutLocation, float & OutAcceptanceRadius)
{
	OutLocation = FVector::ZeroVector;
	OutAcceptanceRadius = AcceptanceRadius;
	CheckNullResult(Path, false);

	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

	return true;
}

void USH_CPatrolComponent::UpdateNextIndex()
{
	CheckNull(Path);

	int32 count = Path->GetSpline()->GetNumberOfSplinePoints();

	if (bReverse)
	{
		if (Index > 0)
		{
			Index--;
			return;
		}

		if (Path->GetSpline()->IsClosedLoop())
		{
			Index = count - 1;
			return;
		}

		Index = 1;
		bReverse = false;
		return;
	}

	if (Index < count - 1)
	{
		Index++;
		return;
	}

	if (Path->GetSpline()->IsClosedLoop())
	{
		Index = 0;
		return;
	}

	Index = count - 2;
	bReverse = true;
}


