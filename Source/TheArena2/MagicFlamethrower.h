// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Magic.h"
#include "MagicFlames.h"
#include "MagicFlamethrower.generated.h"


/**
 * 
 */
UCLASS()
class THEARENA2_API AMagicFlamethrower : public AMagic
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		UClass* Flames;
	AMagicFlames* FlameComponent;

	// If the flames should be on or not. The component might still exist because we don't destroy it manually
	// and instead sets its lifespan
	bool FlamesOn = false;

	virtual void CastSpell(ACharacter* Caster) override;
	virtual void StopSpell(ACharacter* Caster) override;
};
