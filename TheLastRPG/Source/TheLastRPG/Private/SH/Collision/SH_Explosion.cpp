#include "SH/Collision/SH_Explosion.h"
#include "SH/SH_Global.h"
#include "Particles/ParticleSystemComponent.h"

ASH_Explosion::ASH_Explosion()
{
	SH_CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");

	UParticleSystem* particle;
	SH_CHelpers::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/ParagonCountess/FX/Particles/Abilities/BlinkStrike/FX/p_Countess_BlinkStrikeFlash.p_Countess_BlinkStrikeFlash'");
	Particle->SetTemplate(particle); // ���ø� �κп� �Ҵ�������.
	Particle->bAutoActivate = false; // �ٷ� �ڵ����� ����Ǵ°� ��.
}

void ASH_Explosion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASH_Explosion::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	Particle->ResetParticles(); // �����������. ������ �ϴ��� �ʱ�ȭ��
	Particle->SetActive(true); // �������� ����
}
