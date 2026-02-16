// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "StalkerAIAgent.h"
#include "DBT_LineOfSight.generated.h"

/**
 * 
 */
UCLASS()
class UDBT_LineOfSight : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

	bool InLineOfSight(AStalkerAIAgent* AIAgent);
	
};
