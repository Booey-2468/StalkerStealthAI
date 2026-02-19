// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StealthAIAgent.h"

#include "BehaviorTree/BehaviorTree.h"

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
	UBehaviorTree* Behaviourtree;

	UPROPERTY(Transient)
	UBlackboardComponent* BB;

	virtual void OnPossess(APawn* InPawn) override;
};
