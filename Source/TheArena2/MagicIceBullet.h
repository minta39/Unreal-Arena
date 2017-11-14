// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Magic.h"
#include "MagicIceBullet.generated.h"

/**
 * 
 */
UCLASS()
class THEARENA2_API AMagicIceBullet : public AMagic
{
	GENERATED_BODY()

public:
		// Will probably change this later on
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		UClass* MagicBullet;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float BulletLaunchImpulse;

		virtual void CastSpell(ACharacter* Caster) override;

};
