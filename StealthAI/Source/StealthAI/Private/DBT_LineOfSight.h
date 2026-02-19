// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "StealthAIAgent.h"
#include "DBT_LineOfSight.generated.h"

/**
 * 
 */
UCLASS()
class UDBT_LineOfSight : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

	void InLineOfSight(AStealthAIAgent* AIAgent);

	bool CalculateRawConditionValue(UBehaviorTreeComponent* OwnerComp, uint8 NodeMemory);

	
	
};
