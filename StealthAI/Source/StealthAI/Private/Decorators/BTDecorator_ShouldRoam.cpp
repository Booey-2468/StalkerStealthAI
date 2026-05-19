// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_ShouldRoam.h"

UBTDecorator_ShouldRoam::UBTDecorator_ShouldRoam()
{
	NodeName = "Should Be Roaming?";
	bCreateNodeInstance = true;
}

bool UBTDecorator_ShouldRoam::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyAIController = OwnerComp.GetAIOwner();

	if (!MyBlackboard || !MyAIController)
	{
		return false;
	}

	return MyBlackboard->GetValueAsBool("IsRecentlyDetected");
}