// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StealthAI/StealthAICharacter.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"

#include "Navmesh/RecastNavMesh.h"
#include "NavigationSystem.h"
#include "AIController.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "StealthAIAgent.generated.h"

UCLASS()
class AStealthAIAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStealthAIAgent();

public:
	// Sets default values for this pawn's properties
	void ChaseObjective(FVector ObjectiveLocation);
	ARecastNavMesh* GetNavmesh();

	USceneComponent* RootComp;

	UAIPerceptionComponent* PawnPerception;

	UPROPERTY(EditAnywhere)
	AAIController* AIController;

	UBehaviorTree* BehaviourTree;

	bool IsInSight;
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
