// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_GeneratePatrolPoint.h"

UBTTask_GeneratePatrolPoint::UBTTask_GeneratePatrolPoint()
{
	NodeName = "Add Last Detected Patrol Point";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_GeneratePatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());
	AStealthAIAgent* MyAgent;

	if (!MyBlackboard || !MyAIController || !(MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn())))
	{
		return EBTNodeResult::Type::Failed;
	}
	float PointDist;
	const FVector& LastKnownLocation = MyBlackboard->GetValueAsVector("LastDetectedLocation");

	for (int i = 0; i < MyAgent->PatrolPoints.Num(); i++)
	{
		PointDist = (LastKnownLocation - MyAgent->PatrolPoints[i]->GetActorLocation()).Length();
		if (PointDist < MyBlackboard->GetValueAsFloat("MinPatrolDist"))
		{
			return EBTNodeResult::Type::Succeeded;
		}
	}
	APatrolPoint* PatrolPoint = GetWorld()->SpawnActor<APatrolPoint>(APatrolPoint::StaticClass(), LastKnownLocation, FQuat::Identity.Rotator());

	if (MyAgent->PatrolPoints.Num() < MyBlackboard->GetValueAsInt("MaxPatrolPoints"))
	{
		MyAgent->PatrolPoints.Emplace(PatrolPoint);
	}
	else	// Uses queue system so that new point gets added to the front of the queue
	{
		MyAgent->PatrolPoints.EmplaceAt(0, PatrolPoint);
		MyAgent->PatrolPoints.RemoveAt(MyAgent->PatrolPoints.Num() - 1);
	}

	return EBTNodeResult::Type::Succeeded;

}
