// Fill out your copyright notice in the Description page of Project Settings.


#include "Service/BTService_OnSeenPlayer.h"

UBTService_OnSeenPlayer::UBTService_OnSeenPlayer()
{
	NodeName = "Update On Seen Player";
	bCreateNodeInstance = true;
}
void UBTService_OnSeenPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	MyBlackboard->SetValueAsBool("IsAlert", true);
	MyBlackboard->SetValueAsFloat("AlertStateTimer", MyBlackboard->GetValueAsFloat("AlertStateTime"));
	MyBlackboard->SetValueAsBool("ShouldStartInDepthRoaming", false);

	MyBlackboard->SetValueAsVector("LastDetectedLocation", Player->GetActorLocation());
}