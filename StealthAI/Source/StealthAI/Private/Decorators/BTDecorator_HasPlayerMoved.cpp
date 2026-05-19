// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_HasPlayerMoved.h"


UBTDecorator_HasPlayerMoved::UBTDecorator_HasPlayerMoved()
{
	NodeName = TEXT("Has Player Moved");
	bCreateNodeInstance = true;
}

bool UBTDecorator_HasPlayerMoved::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	AStealthAICharacter* Player = Cast<AStealthAICharacter>(MyAIController->GetSeenPawn());

	// Also ensures it is the right AI controller and Pawn type being used

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()) || !Player)	// Ensures all Pointers are valid.
	{
		return false;
	}

	float LastQueryDist = (Player->GetActorLocation() - MyBlackboard->GetValueAsVector("LastQueriedLocation")).Length();
	bool IsOutOfRange = MyBlackboard->GetValueAsFloat("DistFromPlayer") < MyBlackboard->GetValueAsFloat("MinFiringRange") || MyBlackboard->GetValueAsFloat("DistFromPlayer") > MyBlackboard->GetValueAsFloat("MaxFiringRange");
	// Sets to true if player distance from last EQS query point is bigger than Min Query Dist or if the player has passed the min firing range
	return (LastQueryDist > MyBlackboard->GetValueAsFloat("MinQueryDist") || IsOutOfRange) ? true : false;
}