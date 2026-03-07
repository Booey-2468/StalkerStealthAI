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

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "GameFramework/CharacterMovementComponent.h"

#include "StealthAIAgent.generated.h"

class ACustomAIController;

UCLASS()
class AStealthAIAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStealthAIAgent();

public:
	// Sets default values for this pawn's properties
	ARecastNavMesh* GetNavmesh();

	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviourTree;

	ACustomAIController* AIController;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
