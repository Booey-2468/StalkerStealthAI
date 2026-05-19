// Fill out your copyright notice in the Description page of Project Settings.


#include "Service/BTService_UpdatePlayerShooting.h"

UBTService_UpdateOnLostSight::UBTService_UpdateOnLostSight()
{
	NodeName = "Update On Lost Sight";
	bCreateNodeInstance = true;
}
void UBTService_UpdateOnLostSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	AStealthAIAgent* MyAgent;

	if (!MyBlackboard || !MyAIController || !(MyAgent = Cast<AStealthAIAgent>(MyAIController->GetPawn())))
	{
		return;	//Ensures all pointers are valid
	}
	//Checks if the player has been seen
	MyBlackboard->SetValueAsBool("IsShooting", false);
	UCharacterMovementComponent* Movement = MyAgent->GetCharacterMovement();

	if (MyBlackboard->GetValueAsBool("IsPatrolling"))
		Movement->MaxWalkSpeed = 300.0f;
	else
		Movement->MaxWalkSpeed = 600.0f;

	Movement->bOrientRotationToMovement = true;
}