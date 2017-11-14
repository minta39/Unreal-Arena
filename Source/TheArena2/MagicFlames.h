// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MagicFlames.generated.h"

UCLASS()
class THEARENA2_API AMagicFlames : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicFlames();

	// We have this so that we can inilialize some stuff
	AMagicFlames(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame. Will be used to do over time damage
	virtual void Tick( float DeltaTime ) override;

	// How much damage the magic does
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		float Damage;
	// The ParticleSystem to make the thing much cooler
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		//UParticleSystem* ParticleSystem;

	USceneComponent* SceneComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Magic")
		UParticleSystemComponent* ParticleComponent;
	// The Box that can collide with things to do damage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
		UBoxComponent* ProxBox;
	// Particle effect when it hits somethings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		UParticleSystem* ParticleExplosion;
};
