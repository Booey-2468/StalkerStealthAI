// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_ShouldBeginDeepRoam.h"


UBTDecorator_ShouldBeginDeepRoam::UBTDecorator_ShouldBeginDeepRoam()
{
	NodeName = TEXT("Should Start In Depth Roaming");
	bCreateNodeInstance = true;
}

bool UBTDecorator_ShouldBeginDeepRoam::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()))
	{
		return false;
	}


	return MyBlackboard->GetValueAsBool("ShouldStartInDepthRoaming");
}