// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_IsInRange.h"

UBTDecorator_IsInRange::UBTDecorator_IsInRange()
{
	NodeName = "Is In Range";
	bCreateNodeInstance = true;
}

bool UBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	if (!MyBlackboard)
	{
		return false;
	}
	float DistFromPlayer = MyBlackboard->GetValueAsFloat("DistFromPlayer");
	bool InRange = DistFromPlayer < MyBlackboard->GetValueAsFloat("MaxFiringRange") && DistFromPlayer > MyBlackboard->GetValueAsFloat("MinFiringRange");
	return InRange;
}