// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "Magic.h"


// Sets default values
AMagic::AMagic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMagic::AMagic(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{

	SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));
	RootComponent = SceneComponent;

	ParticleSystem = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystem"));
	ParticleSystem->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMagic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagic::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMagic::CastSpell(ACharacter* Caster)
{
	UGameplayStatics::SpawnEmitterAttached(ParticleCast, Caster->GetMesh(), "LeftHandSocket");
}
void AMagic::StopSpell(ACharacter* Caster)
{

}