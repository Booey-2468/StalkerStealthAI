// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_RotateTowardsPoint.h"

UBTTask_RotateTowardsPoint::UBTTask_RotateTowardsPoint()
{
	NodeName = "Rotate Towards";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_RotateTowardsPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());
	AStealthAIAgent* MyAgent;

	if (!MyBlackboard || !MyAIController || !(MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn())))	// Ensures Pointers are valid
	{
		return EBTNodeResult::Type::Failed;
	}
	FVector BetweenVector = MyAIController->GetSeenPawn()->GetActorLocation() - MyAgent->GetActorLocation();
	BetweenVector = FVector::VectorPlaneProject(BetweenVector, FVector::UpVector);
	BetweenVector.Normalize();	// Gets direction vector from player pawn and AI Agent to use for rotation when in line of sight


	MyBlackboard->SetValueAsBool("UseCustomRot", true);
	MyBlackboard->SetValueAsRotator("TargetRotation", BetweenVector.Rotation());

	return EBTNodeResult::Type::Succeeded;

}