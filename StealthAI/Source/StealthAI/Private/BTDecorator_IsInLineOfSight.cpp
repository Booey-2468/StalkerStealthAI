// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInLineOfSight.h"

UBTDecorator_IsInLineOfSight::UBTDecorator_IsInLineOfSight()
{
	NodeName = "IsInLineOfSight";
	bCreateNodeInstance = true;
}

bool UBTDecorator_IsInLineOfSight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyAIController = OwnerComp.GetAIOwner();

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