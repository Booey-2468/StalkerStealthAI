// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerAIAgent.h"

// Sets default values
AStalkerAIAgent::AStalkerAIAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("PawnMesh");
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensor");
	AIController = CreateDefaultSubobject<AAIController>("StalkerAIController")

}

void AStalkerAIAgent::ChaseObjective(FVector ObjectiveLocation)
{
	ARecastNavMesh* NavMesh = GetNavmesh();

	AIController->MoveToLocation(ObjectiveLocation, 15.0f, true, true, true, true, , false);
}

ARecastNavMesh* AStalkerAIAgent::GetNavmesh()
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (!NavSystem)
		return nullptr;

	return Cast<ARecastNavMesh>(NavSystem->GetDefaultNavDataInstance());
}

// Called when the game starts or when spawned
void AStalkerAIAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStalkerAIAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
