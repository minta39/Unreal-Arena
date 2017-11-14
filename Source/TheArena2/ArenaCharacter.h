// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Magic.h"
#include "GameFramework/Character.h"
#include "ArenaCharacter.generated.h"

UCLASS()
class THEARENA2_API AArenaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArenaCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called when destroyed?
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Forward function and right functions for the input commands
	void Forward(float amount);
	void Right(float amount);

	// Camera control function for the input commands
	void MouseYaw(float amount);
	void MousePitch(float amount);

	// Mouse sensitivity for the camera control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
		float MouseSensitivity = 200;

	/** MovementSpeed. The character will use this variable to adjust the movement input*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementSpeed = 0.5f;

	// Avoid ability
	void Avoid();
	FTimerHandle AvoidTimerHandle;
	bool bCanAvoid = true;
	void CanAvoid();

	//Attacks with this function. Called by input
	void Attack();
	void StopAttack();

	// Kind of like a contructor but it runs after most of the things have spawned in. Even after blueprint stuff
	virtual void PostInitializeComponents() override;

	// Spellbook for the player. Can add spells to it in a blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		TArray<UClass*> SpellBook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		TArray<AMagic*> Spells;
	AMagic* Magic;

	// Switches the spell up if true, otherwise down
	void SwitchSpellUp(bool up);

	// Equips the current spell
	void EquipSpell();

	// Called by the scroll wheel inputs to switch spells
	void SwitchUp();
	void SwitchDown();

	// Begins the attack cooldown so that the spells can decide on when to start them
	void BeginAttackCooldown(float length);

	// sets bCanAttack to false
	void CannotAttack();
	// sets bCanAttack to true
	void CanAttack();
	// Timer Handle for the attack
	FTimerHandle AttackTimerHandle;

	// Hitpoints for the character. If it goes down to 0 then the character dies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		float HitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		UParticleSystem* AvoidEffect;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
	// Index of the current spell used
	int CurrentSpell = 0;
	// Used for attack cooldown
	bool bCanAttack = true;
};
