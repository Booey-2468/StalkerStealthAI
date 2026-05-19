// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "BTTask_RotateTowardsPoint.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTTask_RotateTowardsPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UBTTask_RotateTowardsPoint();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
