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
	AStealthAICharacter* Player = Cast<AStealthAICharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()) && !Player)
	{
		return false;
	}

	return MyBlackboard->GetValueAsBool("IsRecentlyDetected");
}