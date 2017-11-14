// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "MagicFlames.h"


// Sets default values
AMagicFlames::AMagicFlames()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
AMagicFlames::AMagicFlames(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{

	SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));
	RootComponent = SceneComponent;
	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	ProxBox->AttachTo(RootComponent);
	ProxBox->Activate();

	ParticleComponent = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystem"));
	ParticleComponent->AttachTo(RootComponent);
	
	Damage = 0.5f;

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMagicFlames::BeginPlay()
{
	Super::BeginPlay();
	/*if (ParticleSystem)
	{
		ParticleComponent = UGameplayStatics::SpawnEmitterAttached(ParticleSystem, RootComponent);
	}*/
}

// Called every frame 
void AMagicFlames::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TArray<AActor*> actors;
	TArray<AActor*> tempActors;

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
		if (actors[i] && ProxBox->IsOverlappingComponent(enemy->GetCapsuleComponent()))
		{
			if(actors[i]->TakeDamage(Damage * DeltaTime, FDamageEvent(), 0, this) > 0)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleExplosion, enemy->GetActorLocation());
		}
	}

}


