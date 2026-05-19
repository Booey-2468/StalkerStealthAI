// Fill out your copyright notice in the Description page of Project Settings.

#include "Decorators/BTDecorator_IsInLineOfSight.h"

UBTDecorator_IsInLineOfSight::UBTDecorator_IsInLineOfSight()
{
	NodeName = TEXT("Is In Line Of Sight");
	bCreateNodeInstance = true;
}

bool UBTDecorator_IsInLineOfSight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()))	// Ensures all Pointers are valid.
	{
		return false;
	}
	return (Cast<AStealthAICharacter>(MyAIController->GetSeenPawn())) ? true : false;
}