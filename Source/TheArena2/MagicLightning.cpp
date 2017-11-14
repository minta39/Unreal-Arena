// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "MagicLightning.h"
#include "ArenaCharacter.h"

AMagicLightning::AMagicLightning(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	ProxBox->AttachTo(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void AMagicLightning::CastSpell(ACharacter* Caster)
{
	Super::CastSpell(Caster);
	if (ParticleLightning)
	{
		TArray<AActor*> actors;
		TArray<AActor*> tempActors;
		int32 particleIndex = 0;
		int32 targets = 0;

		ProxBox->GetOverlappingActors(tempActors);

		for (int i = 0; i < tempActors.Num(); i++)
		{
			if (Cast<ACharacter>(tempActors[i]))
			{
				actors.Add(tempActors[i]);
			}
		}
		for (int i = 0; i < actors.Num(); i++)
		{
			ACharacter* enemy = Cast<ACharacter>(actors[i]);
			if (actors[i] && ProxBox->IsOverlappingComponent(enemy->GetCapsuleComponent()) && enemy != Caster && targets < MaxTargets)
			{
				if (actors[i]->TakeDamage(Damage, FDamageEvent(), 0, this) > 0)
				{
					ParticleComponent.Add(UGameplayStatics::SpawnEmitterAttached(ParticleLightning, Caster->GetMesh(), "LeftHandSocket"));
					ParticleComponent[particleIndex]->SetBeamTargetPoint(0, enemy->GetMesh()->GetBoneLocation("Spine2"), 0);
					particleIndex++;
					Actors.Add(enemy);

					targets++;

					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleExplosion, enemy->GetMesh()->GetBoneLocation("Spine2"));

					if (LightningHitSound)
					{
						UGameplayStatics::PlaySoundAtLocation(GetWorld(), LightningHitSound, actors[i]->GetActorLocation());
					}
				}
			}
		}

		Cast<AArenaCharacter>(Caster)->BeginAttackCooldown(1.f);
		if (ParticleComponent.Num() > 0 && Actors.Num() > 0)
		GetWorldTimerManager().SetTimer(ParticleArrayTimer, this, &AMagicLightning::EmptyParticleArray, 0.8f, false);
	}
}
void AMagicLightning::StopSpell(ACharacter* Caster)
{
}

void AMagicLightning::EmptyParticleArray()
{
	for (int i = 0; i < ParticleComponent.Num(); i++)
	{
		ParticleComponent[i]->DestroyComponent();
	}
	ParticleComponent.Empty();
	Actors.Empty();
}

void AMagicLightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ParticleComponent.Num() > 0)
	{
		for (int i = 0; i < ParticleComponent.Num(); i++)
		{
			if (ParticleComponent[i] && Actors[i])
			{
				ParticleComponent[i]->SetBeamTargetPoint(0, Actors[i]->GetMesh()->GetBoneLocation("Spine2"), 0);
			}
		}
	}
}
