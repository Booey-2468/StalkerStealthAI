// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "CustomAIController.h"
#include "StealthAIAgent.h"
#include "StealthAI/StealthAICharacter.h"

#include "BTTask_GeneratePatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTTask_GeneratePatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_GeneratePatrolPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
