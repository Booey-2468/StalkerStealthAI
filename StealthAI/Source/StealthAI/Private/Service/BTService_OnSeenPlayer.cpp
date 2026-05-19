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
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	AStealthAICharacter* Player;	
	AStealthAIAgent* MyAgent;

	if (!MyBlackboard || !MyAIController || !(MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn())) || !(Player = Cast<AStealthAICharacter>(MyAIController->GetSeenPawn())))
	{
		return;	//Ensures all pointers are valid
	}

	MyBlackboard->SetValueAsVector("PlayerVelocity", Player->GetVelocity());	// Records velocity for later deep roaming

	float DistFromPlayer = (Player->GetActorLocation() - MyAgent->GetActorLocation()).Length();
	UCharacterMovementComponent* Movement = MyAgent->GetCharacterMovement();

	Movement->bOrientRotationToMovement = false;
	Movement->MaxWalkSpeed = 600.0f;

	MyBlackboard->SetValueAsBool("IsShooting", true);

	MyBlackboard->SetValueAsBool("HasHeard", false);

	MyBlackboard->SetValueAsFloat("DistFromPlayer", DistFromPlayer);	// Records distance for range checks

	MyBlackboard->SetValueAsBool("IsAlert", true);	// Sets IsAlert to true and starts timer 
	MyBlackboard->SetValueAsFloat("AlertStateTimer", MyBlackboard->GetValueAsFloat("AlertStateTime"));

	MyBlackboard->SetValueAsBool("IsRecentlyDetected", false);	// Ensures deep roaming and recently detected are reset
	MyBlackboard->SetValueAsBool("ShouldStartInDepthRoaming", false);

	MyBlackboard->SetValueAsVector("LastDetectedLocation", Player->GetActorLocation());	// Sets last detected location for later roaming

	MyBlackboard->SetValueAsBool("IsPatrolling", false);
}