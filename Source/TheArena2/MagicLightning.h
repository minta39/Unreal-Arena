// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Magic.h"
#include "MagicLightning.generated.h"

/**
 * 
 */
UCLASS()
class THEARENA2_API AMagicLightning : public AMagic
{
	GENERATED_BODY()

public:
	AMagicLightning(const class FObjectInitializer& PCIP);

	USceneComponent* SceneComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Magic")
		UBoxComponent* ProxBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		UParticleSystem* ParticleLightning;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Magic")
		TArray<UParticleSystemComponent*> ParticleComponent;
	TArray<ACharacter*> Actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float Damage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		UParticleSystem* ParticleExplosion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		USoundCue* LightningHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	int32 MaxTargets = 2;

	virtual void CastSpell(ACharacter* Caster) override;
	virtual void StopSpell(ACharacter* Caster) override;

	FTimerHandle ParticleArrayTimer;
	void EmptyParticleArray();

	virtual void Tick(float DeltaTime) override;
};
