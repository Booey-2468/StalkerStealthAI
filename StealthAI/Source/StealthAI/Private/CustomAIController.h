// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StealthAIAgent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "Navigation/PathFollowingComponent.h"


#include "CustomAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACustomAIController : public AAIController
{
	GENERATED_BODY()

	ACustomAIController();

public:

	UBehaviorTreeComponent* BehaviourTreeComp;

	UBlackboardComponent* BlackboardComp;

	UAISenseConfig_Sight* SightConfig;

	UAISenseConfig_Hearing* HearingConfig;


	UFUNCTION()
	void UpdatePerceptionVariables(AActor* PercievedActor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* PawnPerception;

	FAISenseID SightID;
	FAISenseID HearingID;

	virtual void OnPossess(APawn* InPawn) override;

	APawn* GetSeenPawn();

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
