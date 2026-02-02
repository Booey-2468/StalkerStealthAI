// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StalkerAI.generated.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "Detour/DetourNavMesh.h"

UCLASS()
class ENEMYAI_API AStalkerAI : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStalkerAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FVector localEyeLevel;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CalculateAStarCost(const FVector& currentPos, const FVector& targetPos, const FVector& vertexPos, float& totalCost);
	void GetAllNeighbouringTiles(FVector vertexPos);
	ARecastNavMesh* GetNavmesh();

};
