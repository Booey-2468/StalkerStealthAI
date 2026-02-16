// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAIController.h"

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AStalkerAIAgent* MyAIAgent = Cast<AStalkerAIAgent>(InPawn);
}