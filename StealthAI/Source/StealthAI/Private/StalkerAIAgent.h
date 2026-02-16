// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"

#include "Navmesh/RecastNavMesh.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "StalkerAIAgent.generated.h"

UCLASS()
class AStalkerAIAgent : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AStalkerAIAgent();
	void ChaseObjective(FVector ObjectiveLocation);
	ARecastNavMesh* GetNavmesh();

	USceneComponent* RootComp;

	UAIPerceptionComponent* PawnPerception;

	UPROPERTY(EditAnywhere)
	AAIController* AIController;

	bool IsInSight;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void UpdatePerceptionVariables(AActor* PercievedActor, FAIStimulus Stimulus);
	void SetupAIPerception();

	FAISenseID SightID;
	FAISenseID HearingID;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
