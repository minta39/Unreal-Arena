// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MagicProjectile.generated.h"

UCLASS()
class THEARENA2_API AMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicProjectile();

	// Constructor to initialize root components
	AMagicProjectile(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// How much damage the magic does
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		float Damage;

	// The visible mesh if we need one. Should be used to test the magic before adding other effects
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
		UStaticMeshComponent* Mesh;
	// The ParticleSystem to make the thing much cooler
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		UParticleSystem* ParticleSystem;
	UParticleSystemComponent* ParticleComponent;
	// The sphere that can collide with things to do damage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
		USphereComponent* ProxSphere;
	// Particle effect when it hits somethings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		UParticleSystem* ParticleExplosion;

	// Gets called when the projectile hits something
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
