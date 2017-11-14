// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class THEARENA2_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	ANPC(const class FObjectInitializer& PCIP);

	void PostInitializeComponents();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
		float HitPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
		float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
		float BaseAttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
		float AttackTimeout;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
		float TimeSinceLastAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sight")
		USphereComponent* SightSphere;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sight")
		USphereComponent* AggroSphere;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sight")
		USphereComponent* AttackRangeSphere;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sight")
		USphereComponent* OuterAttackRangeSphere;
	bool bOuterActive = false;

	// Which sphere the npc should use to track the player
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sight")
	USphereComponent* LockedSphere;
	bool bDead = false;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool isInSightRange();
	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool isInAttackRange();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =MonsterProperties)
		TArray<UClass*> BPMeleeWeapon;
	AActor* MeleeWeapon;

	UFUNCTION(BlueprintCallable, Category = Collision)
		void SwordSwung();

	void NotifyFriendly();
};
