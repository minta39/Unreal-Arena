// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "ArenaCharacter.h"
#include "Magic.h"
#include "MagicProjectile.h"

// Sets default values
AArenaCharacter::AArenaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Kind of like a contructor but it runs after most of the things have spawned in. Even after blueprint stuff. That is why we spawn in
// the stuff because the blueprints knows what stuff we have specified in their settings
void AArenaCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < SpellBook.Num(); i++)
	{
		if (SpellBook[i])
		{
			Spells.Add(GetWorld()->SpawnActor<AMagic>(SpellBook[i]));
			if (Spells[i])
			{
				Spells[i]->AttachRootComponentTo(GetMesh(), "LeftHandSocket", EAttachLocation::SnapToTarget);
				Spells[i]->GetRootComponent()->SetWorldRotation(GetControlRotation());
				Spells[i]->ParticleSystem->Deactivate();
			}
		}
	}
	EquipSpell();
}

// Called every frame
void AArenaCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AArenaCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &AArenaCharacter::Forward);
	InputComponent->BindAxis("Right", this, &AArenaCharacter::Right);
	InputComponent->BindAxis("Yaw", this, &AArenaCharacter::MouseYaw);
	InputComponent->BindAxis("Pitch", this, &AArenaCharacter::MousePitch);

	InputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &AArenaCharacter::Avoid);

	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AArenaCharacter::Attack);
	InputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &AArenaCharacter::StopAttack);

	InputComponent->BindAction("SwitchSpellUp", EInputEvent::IE_Pressed, this, &AArenaCharacter::SwitchUp);
	InputComponent->BindAction("SwitchSpellDown", EInputEvent::IE_Pressed, this, &AArenaCharacter::SwitchDown);
}
// Sends either true or false to SwitchSpellUp
void AArenaCharacter::SwitchUp()
{
	SwitchSpellUp(true);
}
void AArenaCharacter::SwitchDown()
{
	SwitchSpellUp(false);
}

// Will add or subtract CurrentSpell depending on param up and then call EquipSpell
void AArenaCharacter::SwitchSpellUp(bool up)
{
	if (SpellBook.Num() > 0 )
	{
		if (up && CurrentSpell < (SpellBook.Num()-1))
		{
			CurrentSpell++;
			EquipSpell();
		}
		else if (!up && CurrentSpell > 0)
		{
			CurrentSpell--;
			EquipSpell();
		}
	}
}

// Equips the current spell
void AArenaCharacter::EquipSpell()
{
	
	if (Magic)
	{
		Magic->StopSpell(this);
		Magic->ParticleSystem->Deactivate();
	}
	if (Spells[CurrentSpell])
	{
		Magic = Spells[CurrentSpell];
		Magic->ParticleSystem->Activate();
	}
}

void AArenaCharacter::Avoid()
{
	if (bCanAvoid)
	{
		FVector currentVelocity = GetVelocity();
		currentVelocity.Normalize();

		if (currentVelocity != FVector::ZeroVector)
		{
			GetMovementComponent()->Velocity = currentVelocity * 7500;

			GetWorldTimerManager().SetTimer(AvoidTimerHandle, this, &AArenaCharacter::CanAvoid, 1.75f, false);
			bCanAvoid = false;

			if (AvoidEffect)
			{
				UGameplayStatics::SpawnEmitterAttached(AvoidEffect, GetRootComponent());
			}
		}
	}
}

void AArenaCharacter::CanAvoid()
{
	bCanAvoid = true;
}

void AArenaCharacter::Attack()
{
	if (Magic && bCanAttack)
	{
		Magic->CastSpell(this);
	}
}
void AArenaCharacter::StopAttack()
{
	if (Magic)
	{
		Magic->StopSpell(this);
	}
}

// Makes the character go forward. Called by the input command
void AArenaCharacter::Forward(float amount)
{
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();
		AddMovementInput(fwd, amount * MovementSpeed);
	}
}
// Makes the character strafe to the right. Called by the input command
void AArenaCharacter::Right(float amount)
{
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount * MovementSpeed);
	}
}
// Changes the Yaw rotation of the character using the input Mouse X
void AArenaCharacter::MouseYaw(float amount)
{
	AddControllerYawInput(MouseSensitivity * amount * GetWorld()->GetDeltaSeconds());
}
// Changes the Pitch rotation of the character using the input Mouse Y
void AArenaCharacter::MousePitch(float amount)
{
	AddControllerPitchInput(MouseSensitivity * (-amount) * GetWorld()->GetDeltaSeconds());
}

void AArenaCharacter::BeginAttackCooldown(float length)
{
	if (!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
	{
		CannotAttack();
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AArenaCharacter::CanAttack, length, false);
	}
}

void AArenaCharacter::CanAttack()
{
	bCanAttack = true;
}

void AArenaCharacter::CannotAttack()
{
	bCanAttack = false;
}

float AArenaCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, FString::FromInt(HitPoints));

	float tHitPoints = HitPoints;
	if (HitPoints > 0)
		HitPoints -= DamageAmount;

	if (HitPoints <= 0 && GetController())
	{
		GetController()->UnPossess();
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;
		GetMesh()->AddImpulse(DamageCauser->GetRootComponent()->GetComponentRotation().Vector() * 5000 * DamageAmount);

		//RootComponent->DestroyComponent();
		this->SetLifeSpan(10.f);
	}

	return tHitPoints;
}


void AArenaCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
}
