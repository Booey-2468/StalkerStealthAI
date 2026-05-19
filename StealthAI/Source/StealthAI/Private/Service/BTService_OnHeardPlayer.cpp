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
	AStealthAIAgent* MyAgent;
	if (!MyBlackboard || !MyAIController || !(MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn())) || !Player)
	{
		return;		// Ensures All pointers are valid
	}

}