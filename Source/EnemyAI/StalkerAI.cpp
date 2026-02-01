// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerAI.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "Detour/DetourNavMesh.h"

// Sets default values
AStalkerAI::AStalkerAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStalkerAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStalkerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AStalkerAI::CalculateAStarCost(const FVector& currentPos, const FVector& targetPos, const FVector& vertexPos, float& totalCost)
{
	FVector vectorDir = vertexPos - currentPos;
	vectorDir.Normalize();
	float distToVertex = FVector::DotProduct(vertexPos - currentPos, vectorDir);
	float euclideanDist = sqrt((currentPos.X - targetPos.X) * 2 + (currentPos.Z - targetPos.Z) * 2);
}

void AStalkerAI::GetAllNeighbouringTiles(FVector vertexPos)
{
	FCollisionQueryParams parameters;
	FHitResult hit;
	FVector start = GetActorLocation();
	FVector end = vertexPos;
	if (ActorLineTraceSingle(hit, start, end, ECC_Visibility, parameters))
	{

	}
}

// Called to bind functionality to input


