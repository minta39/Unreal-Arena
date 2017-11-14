// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "NPC.h"
#include "ArenaCharacter.h"
#include "MeleeWeapon.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ANPC::ANPC(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{

	SightSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
	SightSphere->AttachTo(RootComponent);

	AggroSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("AggroSphere"));
	AggroSphere->AttachTo(RootComponent);

	LockedSphere = AggroSphere;

	AttackRangeSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachTo(RootComponent);

	OuterAttackRangeSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("OuterAttackRangeSphere"));
	OuterAttackRangeSphere->AttachTo(RootComponent);

	MovementSpeed = 20;
	HitPoints = 20;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastAttack = 0;

	PrimaryActorTick.bCanEverTick = true;
}

void ANPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// instantiate the melee weapon if a bp was selected
	int i = 0;
	if (BPMeleeWeapon.Num() > 0)
	{
		i = FMath::RandRange(0, BPMeleeWeapon.Num() - 1);
		if (BPMeleeWeapon[i])
		{
			MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(BPMeleeWeapon[i], FVector(), FRotator());
			if (MeleeWeapon)
			{
				MeleeWeapon->AttachRootComponentTo(GetMesh(), "RightHandSocket", EAttachLocation::SnapToTarget);
			}
		}
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (!bDead)
	{
		// basic intel: move the monster towards the player
		AArenaCharacter* avatar = Cast<AArenaCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (!avatar) return;
		FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
		float distanceToPlayer = toPlayer.Size();
		// If the player is not in the SightSphere of the monster,
		// go back
		if (distanceToPlayer > LockedSphere->GetScaledSphereRadius())
		{
			LockedSphere = AggroSphere;
			return;
		}
		if (LockedSphere == AggroSphere) NotifyFriendly();
		LockedSphere = SightSphere;
		toPlayer /= distanceToPlayer;  // normalizes the vector
									   // Actually move the monster towards the player a bit
		AddMovementInput(toPlayer, MovementSpeed * DeltaTime);

		FRotator toPlayerRotation = toPlayer.Rotation();
		toPlayerRotation.Pitch = 0; // 0 off the pitch
		RootComponent->SetWorldRotation(toPlayerRotation);
	}
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ANPC::SwordSwung()
{
	if (MeleeWeapon)
	{
		Cast<AMeleeWeapon>(MeleeWeapon)->Swing();
	}
}

void ANPC::NotifyFriendly()
{
	TArray<AActor*> tempActors;

	AggroSphere->GetOverlappingActors(tempActors);

	for (int i = 0; i < tempActors.Num(); i++)
	{
		if (Cast<ANPC>(tempActors[i]))
		{
			ANPC* friendly = Cast<ANPC>(tempActors[i]);
			FVector toPlayer = friendly->GetActorLocation() - GetActorLocation();
			float d = toPlayer.Size();
			if (d < AggroSphere->GetScaledSphereRadius())
				friendly->LockedSphere = friendly->SightSphere;
		}
	}
}

float ANPC::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	float tHitPoints = HitPoints;
	if (HitPoints > 0)
	{
		HitPoints -= DamageAmount;
		if (LockedSphere != SightSphere)
		{
			LockedSphere = SightSphere;
			NotifyFriendly();
		}
		
	}
		
	if (HitPoints <= 0 && GetController())
	{
		//GetController()->UnPossess();
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;
		GetMesh()->AddImpulse(DamageCauser->GetRootComponent()->GetComponentRotation().Vector() * 5000 * DamageAmount);
		bDead = true;
		RootComponent->DestroyComponent();
		this->SetLifeSpan(10.f);
		MeleeWeapon->SetLifeSpan(10.f);
	}

	return tHitPoints;
}

bool ANPC::isInSightRange()
{
	AArenaCharacter* avatar = Cast<AArenaCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!avatar) return false;
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	float d = toPlayer.Size();
	return d < LockedSphere->GetScaledSphereRadius();
}
bool ANPC::isInAttackRange()
{
	AArenaCharacter* avatar = Cast<AArenaCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!avatar) return false;
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	float d = toPlayer.Size();

	if (d < AttackRangeSphere->GetScaledSphereRadius() && !bOuterActive)
	{
		bOuterActive = true;
		return true;
	}
	else if (d < OuterAttackRangeSphere->GetScaledSphereRadius() && bOuterActive)
	{
		return true;
	}
	if (MeleeWeapon)
	{
		Cast<AMeleeWeapon>(MeleeWeapon)->Rest();
	}
	bOuterActive = false;
	return false;
}

