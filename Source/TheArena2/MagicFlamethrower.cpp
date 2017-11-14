// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "MagicFlamethrower.h"
#include "ArenaCharacter.h"

void AMagicFlamethrower::CastSpell(ACharacter* Caster)
{
	Super::CastSpell(Caster);
	if (Flames)
	{
		FVector fwd = Caster->GetControlRotation().Vector();

		FlameComponent = GetWorld()->SpawnActor<AMagicFlames>(Flames);
		if (FlameComponent)
		{
			FlameComponent->AttachRootComponentTo(Caster->GetMesh(), "LeftHandSocket", EAttachLocation::SnapToTarget);
			FlameComponent->GetRootComponent()->SetWorldRotation(Caster->GetControlRotation());
			FlamesOn = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, "Couldn't Cast Spell");
		}
	}
}
void AMagicFlamethrower::StopSpell(ACharacter* Caster)
{
	if (FlameComponent && FlamesOn)
	{
		FlameComponent->ParticleComponent->Deactivate();
		FlameComponent->ProxBox->DestroyComponent();
		FlameComponent->SetLifeSpan(0.8f);
		FlamesOn = false;
		Cast<AArenaCharacter>(Caster)->BeginAttackCooldown(1.f);
	}
}



