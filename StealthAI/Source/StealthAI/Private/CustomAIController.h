// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StealthAIAgent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "Delegates/DelegateCombinations.h"

#include "Components/AudioComponent.h"

#include "Navigation/PathFollowingComponent.h"

#include "SpawnableBullet.h"

#include "CustomAIController.generated.h"

// Declares Class of Event Dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMultiDispatcher);

UCLASS()
class ACustomAIController : public AAIController
{
	GENERATED_BODY()

	/// <summary>
	/// Sets AI Perception Config and Default behaviour tree and blackboard as well as allowing strafing
	/// </summary>
	ACustomAIController();

	// Initially used as a singleton in a blueprint function library class but ended up not working as I needed an event dispatcher per AI if I implement multiple AI
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatcher")
	FMultiDispatcher ShootBulletEventDispatcher;

	UAISenseConfig_Sight* SightConfig;

	UAISenseConfig_Hearing* HearingConfig;

	FAISenseID SightID;
	FAISenseID HearingID;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* GunFireComp;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* FootstepsComp;

	AStealthAIAgent* MyAgent;

	int CurrentBullet = 0;

	float FiringTimer = 0.0f;

	bool WasMoving = false;

	TArray<TWeakObjectPtr<ASpawnableBullet>> SpawnedBullets;	// Needs to be Weak Object Ptr in order for assignment to detect corrupted/bad pointers

	/// <summary>
	/// Turns on visuals and physics and sets transform of bullet mesh.
	/// Then adds impulse and sets bullet life timer.
	/// </summary>
	/// <param name="Bullet"> Reference to bullet class. </param>
	/// <param name="SpawnLocation"> Used for location to move bullet</param>
	/// <param name="ShootingForce"> Used for initial rotation and impulse force. </param>
	void EnableBulletVisuals(ASpawnableBullet& Bullet, const FVector& SpawnLocation, FVector& ShootingForce);

	/// <summary>
	/// Raycasts Bullet Line and Casts to Player Character.
	/// </summary>
	/// <param name="SpawnLocation"> Used as start point and base of end point. </param>
	/// <param name="TraceDir"> Used as direction of trace.</param>
	void BulletLogic(const FVector& SpawnLocation, const FVector& TraceDir, const float& BulletDamage);

	/// <summary>
	/// Shoots Bullets going through magazine and regenerates deleted bullets.
	/// </summary>
	UFUNCTION()			// Needs to be UFunction for event dispatcher
	void ShootBullet();
public:

	UBehaviorTreeComponent* BehaviourTreeComp;

	UBlackboardComponent* BlackboardComp;

	/// <summary>
	/// Used for access of player character when in line of sight from the AI controller
	/// </summary>
	/// <returns> The Pawn currently seen by the pawn mainly being the player </returns>
	APawn* GetSeenPawn();
private:
	/// <summary>
	/// Delegate of On target perception updated sets enemy actor when seen
	/// </summary>
	/// <param name="PercievedActor"> Represents pointer of sensed actor </param>
	/// <param name="Stimulus"> Stimulus data such as type</param>
	UFUNCTION()
	void UpdatePerceptionVariables(AActor* PercievedActor, FAIStimulus Stimulus);	

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* PawnPerception;

	UPROPERTY(EditAnywhere, Category = PawnProperties)
	float TurnSpeed = 0.3f;	// The speed the pawn rotates at

	/// <summary>
	/// Initializes blackboard and starts behaviour tree as well as some other minor setup
	/// </summary>
	/// <param name="InPawn"> Gives access to the pawn the controller is possessing </param>
	virtual void OnPossess(APawn* InPawn) override;

	/// <summary>
	/// Used for starting in depth roaming and telling if cover location has been reached.
	/// </summary>
	/// <param name="RequestID"> Necessary for override </param>
	/// <param name="Result"> Necessary for override </param>
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
