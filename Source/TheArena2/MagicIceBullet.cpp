// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "MagicIceBullet.h"
#include "MagicProjectile.h"
#include "ArenaCharacter.h"

void AMagicIceBullet::CastSpell(ACharacter* Caster)
{
	Super::CastSpell(Caster);
	if (MagicBullet)
	{
		FVector fwd = Caster->GetControlRotation().Vector();

		FVector nozzle = Caster->GetMesh()->GetSocketLocation("LeftHandSocket");
		nozzle += fwd * 155;

		AMagicProjectile* Bullet = GetWorld()->SpawnActor<AMagicProjectile>(MagicBullet, nozzle, Caster->GetControlRotation());
		if (Bullet)
		{
			Bullet->ProxSphere->AddImpulse(fwd*BulletLaunchImpulse);
			Cast<AArenaCharacter>(Caster)->BeginAttackCooldown(1.f);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f,FColor::Yellow, "Couldn't Cast Spell" );
		}
	}
	
}
