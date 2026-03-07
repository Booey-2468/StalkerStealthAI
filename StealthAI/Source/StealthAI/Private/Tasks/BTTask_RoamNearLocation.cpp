// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_RoamNearLocation.h"

UBTTask_RoamNearLocation::UBTTask_RoamNearLocation()
{
	NodeName = "Roam To/Near Location";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_RoamNearLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()))
	{
		return EBTNodeResult::Type::Failed;
	}
	
	MyBlackboard->SetValueAsVector("TargetLocation", MyBlackboard->GetValueAsVector("LastDetectedLocation"));

	return EBTNodeResult::Type::Succeeded;

}