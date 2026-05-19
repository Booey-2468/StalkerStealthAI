// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StealthAI/StealthAICharacter.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"
#include "Sound/SoundCue.h"

#include "Navmesh/RecastNavMesh.h"
#include "NavigationSystem.h"

#include "SpawnPoint.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "GameFramework/CharacterMovementComponent.h"

#include "StealthAIAgent.generated.h"

class ACustomAIController;

UCLASS()
class AStealthAIAgent : public ACharacter
{
	GENERATED_BODY()

	// Sets default values for this character's properties
	AStealthAIAgent();

public:
	// Sets default values for this pawn's properties

	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviourTree;

	UPROPERTY(EditAnywhere)
	UStaticMesh* BulletMesh;	// Allows custom mesh for bullet mesh

	UPROPERTY(EditAnywhere)
	TArray<APatrolPoint*> PatrolPoints;

	UPROPERTY(EditAnywhere)
	USoundCue* ShootingSound;

	UPROPERTY(EditAnywhere)
	USoundCue* FootstepsSound;

	UPROPERTY(EditAnywhere)
	FVector EyeViewPoint;

	UPROPERTY(EditAnywhere)
	FVector GunPoint;

	UPROPERTY(BlueprintReadWrite)
	float EnemyHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyMaxHealth;


protected:
	/// <summary>
	/// Sets AI Perception position
	/// </summary>
	/// <returns> The Location at which AI perception originates from. </returns>
	virtual FVector GetPawnViewLocation() const override;

	/// <summary>
	/// Sets AI Perception Rotation was serious problem where the perception wouldn't turn with the pawn
	/// </summary>
	/// <returns> The Rotation at which AI Perception is oriented </returns>
	virtual FRotator GetViewRotation() const override;

	/// <summary>
	/// Called when game starts and sets AI controller
	/// </summary>
	virtual void BeginPlay() override;

};
