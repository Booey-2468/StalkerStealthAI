// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthAIAgent.h"
#include "CustomAIController.h"


// Sets default values
AStealthAIAgent::AStealthAIAgent()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;	// Doesn't base rotation off of controller rotation
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;	// Makes sure ue5 automatically creates the AI controller

	AIControllerClass = ACustomAIController::StaticClass();	// Allows ue5 to automatically spawn the AI controller with custom class
}

// Called when the game starts or when spawned
void AStealthAIAgent::BeginPlay()
{
	Super::BeginPlay();
	EnemyHealth = EnemyMaxHealth;	// Sets Enemy health to its max
}

FVector AStealthAIAgent::GetPawnViewLocation() const
{
	return GetActorLocation() + EyeViewPoint;
}

FRotator AStealthAIAgent::GetViewRotation() const
{
	return GetActorRotation();
}