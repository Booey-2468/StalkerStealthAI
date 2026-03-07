// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthAIAgent.h"
#include "CustomAIController.h"


// Sets default values
AStealthAIAgent::AStealthAIAgent()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	RootComponent = RootComp;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root Component");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ACustomAIController::StaticClass();
}

ARecastNavMesh* AStealthAIAgent::GetNavmesh()
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (!NavSystem)
		return nullptr;

	return Cast<ARecastNavMesh>(NavSystem->GetDefaultNavDataInstance());
}

// Called when the game starts or when spawned
void AStealthAIAgent::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<ACustomAIController>(GetController());
}

// Called every frame
void AStealthAIAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


