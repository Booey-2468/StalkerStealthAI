// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_HasHeardSomething.h"


UBTDecorator_HasHeardSomething::UBTDecorator_HasHeardSomething()
{
	NodeName = TEXT("Has Heard Something");
	bCreateNodeInstance = true;
}

bool UBTDecorator_HasHeardSomething::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	if (!MyBlackboard || !MyAIController)	// Ensures all Pointers are valid.
	{
		return false;
	}
	return MyBlackboard->GetValueAsBool("HasHeard");
}