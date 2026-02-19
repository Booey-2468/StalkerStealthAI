// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAIController.h"

ACustomAIController::ACustomAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("Black Board");
	BehaviourTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("Behaviour Tree");
}

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AStealthAIAgent* MyAIAgent = Cast<AStealthAIAgent>(InPawn);

	BlackboardComp->InitializeBlackboard(*MyAIAgent->BehaviourTree->BlackboardAsset);
	BehaviourTreeComp->StartTree(*MyAIAgent->BehaviourTree);
}