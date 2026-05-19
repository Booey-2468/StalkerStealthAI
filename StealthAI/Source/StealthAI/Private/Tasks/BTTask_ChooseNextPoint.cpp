// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_ChooseNextPoint.h"

UBTTask_ChooseNextPoint::UBTTask_ChooseNextPoint()
{
	NodeName = "Choose Next Patrol Point";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ChooseNextPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	AStealthAIAgent* MyAgent;

	if (!MyBlackboard || !MyAIController || !(MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn())))
	{
		return EBTNodeResult::Type::Failed;
	}
	int CurrentPoint = MyBlackboard->GetValueAsInt("CurrentPatrolPoint");

	MyBlackboard->SetValueAsVector("TargetLocation", MyAgent->PatrolPoints[CurrentPoint]->GetActorLocation());

	CurrentPoint = (CurrentPoint >= MyAgent->PatrolPoints.Num() - 1) ? 0 : CurrentPoint + 1;	// Used to wrap around patrol points making a circular patrol rather than a back and forth

	MyBlackboard->SetValueAsInt("CurrentPatrolPoint", CurrentPoint);

	return EBTNodeResult::Type::Succeeded;

}
