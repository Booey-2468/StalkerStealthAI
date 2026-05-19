// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_ShootGun.h"

UBTTask_ShootGun::UBTTask_ShootGun()
{
	NodeName = "Start Shooting Gun";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ShootGun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());
	AStealthAIAgent* MyAgent;

	if (!MyBlackboard || !MyAIController || !(MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn())))
	{
		return EBTNodeResult::Type::Failed;
	}
	if (!MyBlackboard->GetValueAsBool("IsShooting"))
	{
		MyBlackboard->SetValueAsBool("IsShooting", true);
	}
	return EBTNodeResult::Type::Succeeded;
}