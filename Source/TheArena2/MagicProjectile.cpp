// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "MagicProjectile.h"


// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMagicProjectile::AMagicProjectile(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{

	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	RootComponent = ProxSphere;

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &AMagicProjectile::Prox);

	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh"));
	Mesh->AttachTo(RootComponent);

	//ParticleSystem = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystem"));
	//ParticleSystem->AttachTo(RootComponent);

	Damage = 1;
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (ParticleSystem)
	{
		ParticleComponent = UGameplayStatics::SpawnEmitterAttached(ParticleSystem, RootComponent);
	}
	this->SetLifeSpan(10.f);
}

// Called every frame
void AMagicProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// We'll call this when the projectile hits something
void AMagicProjectile::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent() || !Cast<ACharacter>(OtherActor)) return;
	
	if (OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this) > 0)
	{
		if (ParticleExplosion)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleExplosion, GetActorLocation(), GetActorRotation(), true);
		}
		if (ParticleComponent)
		{
			ParticleComponent->Deactivate();
		}

		RootComponent->DestroyComponent();
	}
	
}

