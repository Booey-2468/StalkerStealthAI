// Fill out your copyright notice in the Description page of Project Settings.


#include "DBT_LineOfSight.h"

void UDBT_LineOfSight::InLineOfSight(AStealthAIAgent* AIAgent)
{
	NodeName = "IsInLineOfSight";
	bCreateNodeInstance = true;
}

bool UDBT_LineOfSight::CalculateRawConditionValue(UBehaviorTreeComponent* OwnerComp, uint8 NodeMemory) 
{
	const UBlackboardComponent* MyBlackboard = OwnerComp->GetBlackboardComponent();
	AAIController* MyAIController = OwnerComp->GetAIOwner();

	if (!MyBlackboard || !MyAIController)
	{
		return false;
	}
	else if (!Cast<AStealthAIAgent>(MyAIController->GetPawn()))
	{
		return false;
	}

	if (MyBlackboard->GetValueAsBool("IsInLineOfSight"))
	{
		return true;
	}
	else
	{
		return false;
	}
}