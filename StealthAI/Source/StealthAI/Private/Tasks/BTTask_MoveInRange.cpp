// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_MoveInRange.h"

UBTTask_MoveInRange::UBTTask_MoveInRange()
{
	NodeName = "Move In or Out Of Range";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_MoveInRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	AStealthAIAgent* Pawn = Cast<AStealthAIAgent>(MyAIController->GetPawn());
	AStealthAICharacter* Player = Cast<AStealthAICharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	if (!MyBlackboard || !MyAIController || !Pawn || !Player)
	{
		return EBTNodeResult::Type::Failed;
	}

	float DistFromPlayer = MyBlackboard->GetValueAsFloat("DistFromPlayer");
	bool IsTooClose = DistFromPlayer < MyBlackboard->GetValueAsFloat("MinFiringRange");
	bool IsTooFar = DistFromPlayer > MyBlackboard->GetValueAsFloat("MaxFiringRange");

	FVector RangeLocation;
	if (IsTooClose)
	{
		RangeLocation = Pawn->GetActorLocation() - Player->GetActorLocation();
		RangeLocation.Normalize();
		RangeLocation = Pawn->GetActorLocation() + (RangeLocation * MyBlackboard->GetValueAsFloat("MinFiringRange"));
	}
	else if (IsTooFar)
	{
		RangeLocation = Player->GetActorLocation();
	}
	else
	{
		RangeLocation = Pawn->GetActorLocation();
	}

	FNavLocation ProjLocation;

	if (!FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld())->ProjectPointToNavigation(RangeLocation, ProjLocation, FVector(5000.0f), nullptr, nullptr))
	{
		return EBTNodeResult::Type::Failed;
	}
	
	MyBlackboard->SetValueAsVector("TargetLocation", ProjLocation.Location);
	return EBTNodeResult::Type::Succeeded;

}