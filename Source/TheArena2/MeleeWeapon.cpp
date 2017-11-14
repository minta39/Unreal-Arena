// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "MeleeWeapon.h"


// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

AMeleeWeapon::AMeleeWeapon(const class FObjectInitializer& PCIP) :
	Super(PCIP)
{
	AttackDamage = 1;
	Swinging = false;
	WeaponHolder = NULL;

	RootComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	Mesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this,TEXT("ProxBox"));
	ProxBox->OnComponentBeginOverlap.AddDynamic(this,&AMeleeWeapon::Prox);
	ProxBox->AttachTo(RootComponent);

}
void AMeleeWeapon::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// don't hit non root components
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return;
	}
	// avoid hitting things while sword isn't swinging,
	// avoid hitting yourself, and
	// avoid hitting the same OtherActor twice
	if (Swinging && OtherActor != WeaponHolder && !ThingsHit.Contains(OtherActor) && !Cast<ANPC>(OtherActor))
	{
		OtherActor->TakeDamage(AttackDamage, FDamageEvent(), 0, this);
		if (BloodSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodSystem, OtherActor->GetRootComponent()->GetComponentLocation());
		}
		ThingsHit.Add(OtherActor);
	}
}
void AMeleeWeapon::Swing() 
{
	ThingsHit.Empty();  // empty the list
	Swinging = true;
}
void AMeleeWeapon::Rest()
{
	ThingsHit.Empty();
	Swinging = false;
}