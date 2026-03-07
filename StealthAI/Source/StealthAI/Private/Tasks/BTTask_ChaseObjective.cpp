// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_ChaseObjective.h"

UBTTask_ChaseObjective::UBTTask_ChaseObjective()
{
	NodeName = "Chase Objective";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ChaseObjective::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());
	if(!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()))
	{
		return EBTNodeResult::Type::Failed;
	}
	float DistFromPlayer = MyBlackboard->GetValueAsFloat("DistFromPlayer");
	MyAIController->MoveToLocation(MyBlackboard->GetValueAsVector("TargetLocation"), 15.0f, true, true, true, true);

	return EBTNodeResult::Type::Succeeded;

}