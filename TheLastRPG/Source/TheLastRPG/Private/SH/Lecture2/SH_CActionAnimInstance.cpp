#include "SH/Lecture2/SH_CActionAnimInstance.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"


void USH_CActionAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	SH_CheckNull(character);

	USH_CActionComponent* action = SH_CHelpers::GetComponent<USH_CActionComponent>(character);
	SH_CheckNull(action);

	action->OnActionTypeChanged.AddDynamic(this, &USH_CActionAnimInstance::OnActionTypeChanged);
}

void USH_CActionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	SH_CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());

	USH_CFeetComponent* feet = SH_CHelpers::GetComponent<USH_CFeetComponent>(character);
	if (!!feet)
		FeetData = feet->GetData();
}

void USH_CActionAnimInstance::OnActionTypeChanged(ESH_ActionType InPrevType, ESH_ActionType InNewType)
{
	ActionType = InNewType;
}
