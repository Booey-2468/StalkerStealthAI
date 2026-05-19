// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_IsInRange.h"

UBTDecorator_IsInRange::UBTDecorator_IsInRange()
{
	NodeName = "Is Out of Range";
	bCreateNodeInstance = true;
}

bool UBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	if (!MyBlackboard)	// Ensures Pointers are valid.
	{
		return false;
	}
	float DistFromPlayer = MyBlackboard->GetValueAsFloat("DistFromPlayer");	// Stores the distance from the player and uses it in is in range boolean
	bool InRange = (DistFromPlayer < MyBlackboard->GetValueAsFloat("MinFiringRange") || DistFromPlayer > MyBlackboard->GetValueAsFloat("MaxFiringRange"));
	return InRange;
}