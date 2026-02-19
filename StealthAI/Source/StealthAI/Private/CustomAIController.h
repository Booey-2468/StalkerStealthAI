// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StealthAIAgent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


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
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviourTreeComp;

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

	virtual void OnPossess(APawn* InPawn) override;
};
