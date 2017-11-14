// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Magic.generated.h"

UCLASS()
class THEARENA2_API AMagic : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AMagic();

	AMagic(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Root Component for this actor so that there won't be any problems attaching it to a socket.
	USceneComponent* SceneComponent;

	// Particle system. Which is basically what this magic weapon will look like.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="ParticleSystem")
	UParticleSystemComponent* ParticleSystem;

	// Particle system. Should be used to spawn at the hands of the caster when activating a spell
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		UParticleSystem* ParticleCast;

	virtual void CastSpell(ACharacter* Caster);
	virtual void StopSpell(ACharacter* Caster);
	
};
