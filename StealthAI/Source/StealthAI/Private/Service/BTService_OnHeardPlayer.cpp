// Fill out your copyright notice in the Description page of Project Settings.


#include "Service/BTService_OnHeardPlayer.h"

UBTService_OnHeardPlayer::UBTService_OnHeardPlayer()
{
	NodeName = "Update On Heard Player";
	bCreateNodeInstance = true;
}
void UBTService_OnHeardPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyAIController = OwnerComp.GetAIOwner();

	AStealthAICharacter* Player = Cast<AStealthAICharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()) || !Player)
	{
		return;
	}

	AStealthAIAgent* MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn());

	MyBlackboard->SetValueAsVector("PlayerVelocity", Player->GetVelocity());

	float DistFromPlayer = (Player->GetActorLocation() - MyAgent->GetActorLocation()).Length();

	MyBlackboard->SetValueAsFloat("DistFromPlayer", DistFromPlayer);

	float MaxFiringDist = MyBlackboard->GetValueAsFloat("MaxFiringRange");
	float MinFiringDist = MyBlackboard->GetValueAsFloat("MinFiringRange");
	if (DistFromPlayer < MinFiringDist)
	{
		FVector RetreatLocation = (UE::Math::TVector<double>)(MinFiringDist - DistFromPlayer) * (MyAgent->GetActorLocation() - Player->GetActorLocation()).Normalize();
		FNavLocation ProjLocation;
		if (!FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld())->ProjectPointToNavigation(RetreatLocation, ProjLocation, FVector(100.0f), nullptr, nullptr))
		{
			return;
		}
		;
		MyBlackboard->SetValueAsVector("TargetLocation", ProjLocation);
	}
	else if (DistFromPlayer > MaxFiringDist)
	{
		MyBlackboard->SetValueAsVector("TargetLocation", Player->GetActorLocation());
	}


}