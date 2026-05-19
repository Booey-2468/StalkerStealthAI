// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_ShouldPatrol.h"

UBTDecorator_ShouldPatrol::UBTDecorator_ShouldPatrol()
{
	NodeName = "Should Patrol?";
	bCreateNodeInstance = true;
}

bool UBTDecorator_ShouldPatrol::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyAIController = OwnerComp.GetAIOwner();

	if (!MyBlackboard || !MyAIController)
	{
		return false;
	}

	return MyBlackboard->GetValueAsBool("IsPatrolling");
}