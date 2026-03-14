// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_IsNotMoving.h"

UBTDecorator_IsNotMoving::UBTDecorator_IsNotMoving()
{
	NodeName = TEXT("Is Not Moving");
	bCreateNodeInstance = true;
}

bool UBTDecorator_IsNotMoving::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()))
	{
		return false;
	}

	return MyAIController->GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Idle || MyAIController->GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Waiting;
}